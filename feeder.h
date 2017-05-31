
//Header file for feeder

void csvPaktReader(char layer2[], FILE *fptr);
void l2PayLoadExtractor(char layer2[], char l2payload[]);
void feeder();
void progressReport(int queue);
