#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 50
#define HIDDEN_SIZE 100
#define OUTPUT_SIZE 1
#define SEQ_LENGTH 500
#define PREDICT_SEQ_LENGTH 10
#define LEARNING_RATE 0.001
#define EPOCHS 10

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of the sigmoid activation function
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Calculate dot product of two vectors
double dot_product(double *vec1, double *vec2, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

// Hyperbolic tangent derivative function
double tanh_derivative(double x) {
    return 1.0 - pow(tanh(x), 2);
}

typedef struct {
    double *input_weights;
    double *forget_weights;
    double *output_weights;
    double *cell_weights;

    double *input_bias;
    double *forget_bias;
    double *output_bias;
    double *cell_bias;

    double *hidden_state;
    double *cell_state;

    double *output;
} LSTM_Cell;

// Initialize LSTM cell
LSTM_Cell *init_lstm_cell() {
    LSTM_Cell *cell = (LSTM_Cell*)malloc(sizeof(LSTM_Cell));

    cell->input_weights = (double*)malloc(sizeof(double) * HIDDEN_SIZE * (INPUT_SIZE + HIDDEN_SIZE));
    cell->forget_weights = (double*)malloc(sizeof(double) * HIDDEN_SIZE * (INPUT_SIZE + HIDDEN_SIZE));
    cell->output_weights = (double*)malloc(sizeof(double) * HIDDEN_SIZE * (INPUT_SIZE + HIDDEN_SIZE));
    cell->cell_weights = (double*)malloc(sizeof(double) * HIDDEN_SIZE * (INPUT_SIZE + HIDDEN_SIZE));

    cell->input_bias = (double*)malloc(sizeof(double) * HIDDEN_SIZE);
    cell->forget_bias = (double*)malloc(sizeof(double) * HIDDEN_SIZE);
    cell->output_bias = (double*)malloc(sizeof(double) * HIDDEN_SIZE);
    cell->cell_bias = (double*)malloc(sizeof(double) * HIDDEN_SIZE);

    cell->hidden_state = (double*)malloc(sizeof(double) * HIDDEN_SIZE);
    cell->cell_state = (double*)malloc(sizeof(double) * HIDDEN_SIZE);

    cell->output = (double*)malloc(sizeof(double) * OUTPUT_SIZE);

    // Initialize weights and biases randomly (you can use better initialization methods)
    // Initialize hidden state and cell state to zeros

    return cell;
}

// Forward pass through LSTM cell
void forward_pass(LSTM_Cell *cell, double *input) {
    // Forget gate
    double forget_gate = sigmoid(cell->forget_bias[0] + dot_product(cell->forget_weights, input, HIDDEN_SIZE));

    // Input gate
    double input_gate = sigmoid(cell->input_bias[0] + dot_product(cell->input_weights, input, HIDDEN_SIZE));

    // Output gate
    double output_gate = sigmoid(cell->output_bias[0] + dot_product(cell->output_weights, input, HIDDEN_SIZE));

    // Candidate cell state
    double candidate_cell_state = tanh(cell->cell_bias[0] + dot_product(cell->cell_weights, input, HIDDEN_SIZE));

    // Update cell state
    cell->cell_state[0] = cell->cell_state[0] * forget_gate + input_gate * candidate_cell_state;

    // Update hidden state
    cell->hidden_state[0] = output_gate * tanh(cell->cell_state[0]);

    // Calculate output
    cell->output[0] = cell->hidden_state[0];
}

// Backward pass through LSTM cell (for updating weights)
void backward_pass(LSTM_Cell *cell, double *input, double *expected_output) {
    // Calculate error
    double error = cell->output[0] - expected_output[0];

    // Calculate derivatives
    double d_output = error;
    double d_hidden = d_output * tanh_derivative(cell->hidden_state[0]);
    double d_cell = d_hidden * cell->output[0] * tanh_derivative(cell->cell_state[0]);

    // Update biases
    cell->input_bias[0] -= LEARNING_RATE * d_cell;
    cell->forget_bias[0] -= LEARNING_RATE * d_cell;
    cell->output_bias[0] -= LEARNING_RATE * d_hidden;
    cell->cell_bias[0] -= LEARNING_RATE * d_hidden;

    // Update weights
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        cell->input_weights[i] -= LEARNING_RATE * d_cell * cell->hidden_state[i] * sigmoid_derivative(cell->input_weights[i]);
        cell->forget_weights[i] -= LEARNING_RATE * d_cell * cell->hidden_state[i] * sigmoid_derivative(cell->forget_weights[i]);
        cell->output_weights[i] -= LEARNING_RATE * d_hidden * cell->hidden_state[i] * sigmoid_derivative(cell->output_weights[i]);
        cell->cell_weights[i] -= LEARNING_RATE * d_cell * cell->hidden_state[i] * tanh_derivative(cell->cell_weights[i]);
    }
}

// Train LSTM model
void train_lstm(double *data, LSTM_Cell **pcell) {
    LSTM_Cell *lstm_cell = init_lstm_cell();

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        // Iterate over sequences and update weights
        for (int i = 0; i < SEQ_LENGTH - INPUT_SIZE - 1; i++) {
            double *input_sequence = &data[i];
            double *expected_output = &data[i + INPUT_SIZE];
            forward_pass(lstm_cell, input_sequence);
            backward_pass(lstm_cell, input_sequence, expected_output);
        }
        if(epoch % 50 == 0)
            printf("%d/%d finished\n", epoch, EPOCHS);
    }
    *pcell = lstm_cell;
    // Free memory
}

// Predict next values using trained LSTM model
void predict_values(LSTM_Cell *cell, double *input_sequence, double *predicted_sequence) {
    // Make predictions for the next PREDICT_SEQ_LENGTH values
    for (int i = 0; i < PREDICT_SEQ_LENGTH; i++) {
        forward_pass(cell, input_sequence);
        predicted_sequence[i] = cell->output[0];
        input_sequence++;
    }
}

int main() {
    double data[SEQ_LENGTH]; // Your time series data here
    for(int i = 0; i < SEQ_LENGTH; i++)
    {
        data[i] = sin(i * 3.1415926535 / 2);
    }
    LSTM_Cell *lstm_cell;

    // Train LSTM model
    train_lstm(data, &lstm_cell);

    // Prepare input sequence for prediction
    double input_sequence[INPUT_SIZE];
    for (int i = 0; i < INPUT_SIZE; i++) {
        input_sequence[i] = data[SEQ_LENGTH - INPUT_SIZE + i];
    }

    // Predict next values
    double predicted_sequence[PREDICT_SEQ_LENGTH];
    predict_values(lstm_cell, input_sequence, predicted_sequence);

    // Print predicted values
    printf("Predicted sequence:\n");
    for (int i = 0; i < PREDICT_SEQ_LENGTH; i++) {
        printf("%.8f\n", predicted_sequence[i]);
    }
    printf("\n");

    // Free memory
    // Free LSTM cell and other allocated memory

    return 0;
}
