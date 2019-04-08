#ifndef UTILS_H
#define UTILS_H

void logToFile(double value) {
    dataFile.print(value);
    dataFile.print(",");  // csv syntax
}

#endif // UTILS_H
