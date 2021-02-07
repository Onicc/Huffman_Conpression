#include <cstdio>
#include <string>
#include <iostream>
#include "huffman.h"
#include "exception.h"

using namespace std;

int main()
{
    string filename = "E:/Track/Compress/frame-short-37059.data";
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == nullptr) {
        throw MyException("Failed to open file");
    }

    int frameSize = 72*72;
    auto frameDataPtr = new short[frameSize];
    unordered_map <short, uint32_t> weightMap;
    fread(frameDataPtr, sizeof(short), frameSize, fp);
    fclose(fp);

    Huffman encoder;
    encoder.buildWeightMap(frameDataPtr, frameSize, weightMap);
    encoder.buildHuffmanTree(weightMap);

    for (const auto &iter : weightMap) {
        cout << iter.first << " " << iter.second << endl;
    }
    cout << encoder.huffmanTreeRoot->weight << endl;

    return 0;
}