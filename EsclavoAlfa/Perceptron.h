#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 3)
#include <NeuralNetwork.h>
unsigned int layers[] = {3, 9, 9, 1}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
float *outputs; // 4th layer's outputs (in this case output)

//Default Inputs
const float inputs[8][3] = {
  {0, 0, 0}, //0
  {0, 0, 1}, //1
  {0, 1, 0}, //1
  {0, 1, 1}, //0
  {1, 0, 0}, //1
  {1, 0, 1}, //0
  {1, 1, 0}, //0
  {1, 1, 1}  //1
};
const float expectedOutput[8][1] = {{0}, {1}, {1}, {0}, {1}, {0}, {0}, {1}}; // values that we were expecting to get from the 4th/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.
NeuralNetwork NN(layers, NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates



void Humedad1() {}
void Riego1() {}
// it is 1 for each layer [Pretrained Biases ]
const PROGMEM float biases[] = {1, 1, 0.99308};
// it is 3*9 + 9*9 + 9*1  [Pretrained weights]
const PROGMEM float weights[] = {
  -0.676266,  3.154561, -1.76689 ,
  1.589422, -2.340522,  1.447924,
  0.291685, -1.222407,  0.669717,
  -1.059862,  2.059782, -1.113708,
  -1.790229,  1.472432, -1.903783,
  -5.094713,  7.437615, -5.033135,
  2.341339,  3.370419,  2.185228,
  -3.887402,  1.453663, -3.861217,
  -1.555083,  2.943702, -0.472324,

  -1.171853, -0.45975 , -0.986132, -0.583541, -1.250889, -1.064349, -0.656225, -0.689616, -0.570443,
  -5.30186 ,  1.078257,  0.864669, -2.917707, -2.280059, -2.018297,  1.577451, -3.758011, -4.153339,
  -0.556209, -0.998336, -0.80149 , -0.232561, -1.087017, -1.286771, -1.034251, -0.05806 , -0.415967,
  -1.475901, -0.039556,  0.144446, -0.485774, -0.041879,  0.955343, -1.492304, -0.577319, -0.466558,
  -0.307791, -0.624868, -0.733248, -0.572921,  1.156592,  9.843138, -2.721857, -0.064086, -1.642469,
  -0.824234, -0.440457,  0.180901, -0.683897, -0.487519,  0.189743, -1.430297,  0.238511, -0.824287,
  0.251094, -3.009409, -1.58829 ,  0.590185,  0.597326, -5.243015,  2.710771,  2.596604,  0.969508,
  -1.344488,  2.618552,  0.642735, -0.947158, -0.286999,  3.797427, -2.443925, -0.833397, -1.654542,
  -0.138234, -0.931373, -0.183022, -0.493784, -0.784119, -0.275703, -2.113665,  0.761188, -0.810006,

  -0.049101,
  -6.781154,
  0.14872 ,
  -2.332737,
  -4.983434,
  -1.396086,
  10.86302,
  -5.551509,
  -1.648114

};


void Percepreon1() {
  //NeuralNetwork NN(layers, weights, biases, NumberOf(layers), true);  // Creating a NeuralNetwork with Pretrained Weights and Biases

  //Goes through all inputs
  for (int i = 0; i < NumberOf(inputs); i++)
  {
    outputs = NN.FeedForward(inputs[i], true); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output
    Serial.println(outputs[0], 7); // prints the first 7 digits after the comma.
  }

  NN.print(true); // default is false, true means use of PROGMEM
}

void Inicializar() {

  for (int i = 0; i < 3000; i++) // epochs = Training loops
  {
    for (int j = 0; j < NumberOf(inputs); j++)
    {
      NN.FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
      NN.BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
    }
  }

  //Goes through all inputs
  for (int i = 0; i < NumberOf(inputs); i++)
  {
    outputs = NN.FeedForward(inputs[i]); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output
    Serial.println(outputs[0], 7); // prints the first 7 digits after the comma.
  }

  NN.print(); // prints the weights and biases of each layer
}

void Entrenar() {
  //  NeuralNetwork NN(layers, NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates
  //  //Trains the NeuralNetwork for 8000 epochs = Training loops
  //  for (int i = 0; i < 8000; i++)
  //  {
  //    for (int j = 0; j < NumberOf(inputs); j++)
  //    {
  //      NN.FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
  //      NN.BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.

}





























