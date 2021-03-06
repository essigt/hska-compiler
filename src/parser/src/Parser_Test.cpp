﻿//
// Created by tim on 02.01.17.
//

#include <iostream>

#include "../../scanner/include/Scanner.h"
#include "../include/Parser.h"
#include "../../utils/include/colormod.h"
#include "../include/CodeGenerator.h"


using namespace std;


int main(int argc, char** argv)
{
    std::cout << "--- parser test ---\n" << std::endl;

    if (argc != 2)
    {
        if (argc < 2)
            std::cerr << "One arguments is required." << std::endl;
        else
            std::cerr << "Only one arguments is allowed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Input file: " << argv[1] << "\n" << std::endl;

    auto buffer = new Buffer(argv[1]);
    auto symbolTable = new SymbolTable();
    auto tokenScanner = new TokenScanner();
    auto scanner = new Scanner(buffer, symbolTable, tokenScanner);

    // Do parsing
    auto parser = new Parser(scanner);
    auto tree = parser->parse();
    tree->dumpTree();
    auto valid = tree->typeCheck(tree->getRoot());

    if (valid)
        cout << "type check sucessfully passed" << endl;

    // Generate code
    auto generator = new CodeGenerator();
    generator->generate(tree->getRoot(), std::cout);

    // Cleanup
    delete generator;
    delete tree;
    delete parser;
    delete scanner;
    delete tokenScanner;
    delete symbolTable;
    delete buffer;

#ifdef _WIN32
    system("pause");
#endif
}
