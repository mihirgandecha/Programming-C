bool validateCommandWithNum(const char* command, const char* input) {
    double num;
    char extractedCommand[MAXWORDLEN]; // Assuming MAXWORDLEN is defined

    if (sscanf(input, "%s", extractedCommand) != 1) {
        return false; // Failed to extract the command
    }

    if (strcmp(extractedCommand, command) != 0) {
        return false; // The command part doesn't match
    }

    // Check if the rest of the string has a valid number
    const char* numPart = input + strlen(extractedCommand);
    if (!extractNum(numPart, &num)) {
        return false; // Failed to extract a valid number
    }
    return true; // Successfully validated command and number
}
