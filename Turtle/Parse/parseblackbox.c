void test_openFile(void) {
    printf("Testing openFile...\n");
    FILE* file = openFile("existing_file.txt");
    assert(file != NULL);
    fclose(file);
}