#include <iostream>
#include <bitset>
#include "Tree.h"
#include <string>
#include <stdint-gcc.h>
#include <cstring>
#include <filesystem>

int main() {
    auto root = Tree("/home/stephen/CLionProjects/zipprman/cmake-build-debug/input.txt");
    auto rootptr = root.getRoot();

    std::string ext;
    {
        std::filesystem::path inputPath("input.txt");
        ext = inputPath.extension().string();
    }

    // COMPRESSION
    {
        std::unordered_map<unsigned char, std::string> freq_map;
        std::string encoding;

        Tree::dfs(rootptr, encoding, freq_map);
        std::vector<std::pair<unsigned char, std::string>> canonical_mapping;
        for (const auto& pair : freq_map) {
            canonical_mapping.push_back(pair);
        }

        std::sort(canonical_mapping.begin(), canonical_mapping.end(), [](const auto& a, const auto& b){
            if (a.second.length() != b.second.length()) {
                return a.second.length() < b.second.length();
            } else {
                return a.first < b.first;
            }
        });

        unsigned int code_value = 0;
        std::vector<unsigned char> symbols;

        for (size_t i = 0; i < canonical_mapping.size(); ++i) {
            unsigned char symbol = canonical_mapping[i].first;
            size_t current_len = canonical_mapping[i].second.length();
            size_t next_len = (i + 1 < canonical_mapping.size()) ? canonical_mapping[i + 1].second.length() : current_len;

            std::string canonical_code = std::bitset<32>(code_value).to_string();
            canonical_code = canonical_code.substr(32 - current_len);

            canonical_mapping[i].second = canonical_code;

            code_value++;
            code_value <<= (next_len - current_len);
        }

        std::unordered_map<unsigned char, std::string> canonical_map;
        canonical_map.reserve(canonical_mapping.size());
        for (auto& pair : canonical_mapping) {
            canonical_map[pair.first] = pair.second;
        }

        symbols.reserve(canonical_mapping.size());
        uint32_t num_of_symbols = canonical_mapping.size();

        for (const auto& pair : canonical_mapping) {
            symbols.push_back(pair.first);
        }

        std::ifstream input_file("input.txt", std::ios::binary | std::ios::ate); // used to get the original data
        std::string original_data;
        auto extLen = static_cast<uint16_t>(ext.length());
        std::streampos fileSize = input_file.tellg();
        original_data.resize(fileSize);
        input_file.seekg(0, std::ios::beg);
        input_file.read(&original_data[0], fileSize);
        input_file.close();

        std::ofstream outfile("out.zprm", std::ios::out | std::ios::binary);
        outfile.write(reinterpret_cast<char*>(&extLen), sizeof(extLen));
        outfile.write(ext.c_str(), extLen);
        outfile.write((char*)&num_of_symbols, sizeof(num_of_symbols));
        for (size_t i = 0; i < canonical_mapping.size(); ++i) {
            uint8_t len = canonical_mapping[i].second.length(); // lenght of the code in bits
            outfile.write((char*)&len, sizeof(len));
        }
        outfile.write(reinterpret_cast<char*>(symbols.data()), symbols.size());

        uint64_t bitBuffer = 0;
        int bitsInBuffer = 0;

        for (char c : original_data) {
            std::string code = canonical_map[c];
            for (char bit : code) {
                bitBuffer = (bitBuffer << 1) | (bit - '0');
                bitsInBuffer++;

                while (bitsInBuffer >= 8) {
                    uint8_t byte = (bitBuffer >> (bitsInBuffer - 8)) & 0xFF;
                    outfile.put(byte);
                    bitsInBuffer -= 8;
                }
            }
        }

        if (bitsInBuffer > 0) {
            uint8_t lastByte = (bitBuffer << (8 - bitsInBuffer)) & 0xFF;
            outfile.put(lastByte);
        }

        auto write_size = static_cast<uint64_t>(fileSize);
        outfile.write(reinterpret_cast<char*>(&write_size), sizeof(write_size));

        outfile.close();
    }

    // DECOMPRESSION
    {
        std::ifstream infile("out.zprm", std::ios::binary);

        uint16_t extLen;
        infile.read(reinterpret_cast<char*>(&extLen), sizeof(extLen));

        ext = std::string(extLen, '\0');
        infile.read(ext.data(), extLen);

        uint32_t num_of_symbols;
        infile.read(reinterpret_cast<char*>(&num_of_symbols), sizeof(num_of_symbols));

        std::vector<uint8_t> code_lengths(num_of_symbols);
        infile.read(reinterpret_cast<char*>(code_lengths.data()), num_of_symbols);

        std::vector<unsigned char> symbols(num_of_symbols);
        infile.read(reinterpret_cast<char*>(symbols.data()), num_of_symbols);

        std::unordered_map<unsigned char, std::string> canonical_map;
        unsigned int code_val = 0;
        for (size_t i = 0; i < num_of_symbols; ++i) {
            size_t current_len = code_lengths[i];
            size_t next_len = (i + 1 < num_of_symbols) ? code_lengths[i + 1] : current_len;

            std::string code = std::bitset<32>(code_val).to_string().substr(32 - current_len);
            canonical_map[symbols[i]] = code;

            code_val++;
            code_val <<= (next_len - current_len);
        }

        std::unordered_map<std::string, unsigned char> reverse_map;
        for (const auto& pair : canonical_map) {
            reverse_map[pair.second] = pair.first;
        }

        std::vector<char> buffer((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
        infile.close();

        uint64_t original_size;
        std::memcpy(&original_size, buffer.data() + buffer.size() - 8, 8);
        buffer.resize(buffer.size() - 8);

        std::string current_code;
        std::string decompressed_data;
        decompressed_data.reserve(original_size);

        for (char byte : buffer) {
            for (int i = 7; i >= 0; --i) {
                current_code += ((byte >> i) & 1) ? '1' : '0';
                auto it = reverse_map.find(current_code);
                if (it != reverse_map.end()) {
                    decompressed_data += it->second;
                    current_code.clear();
                    if (decompressed_data.size() >= original_size) break;
                }
            }
            if (decompressed_data.size() >= original_size) break;
        }

        std::string outputFilename = "decompressed" + ext;
        std::ofstream outFile(outputFilename, std::ios::binary);
        outFile.write(decompressed_data.c_str(), decompressed_data.size());
        outFile.close();
    }

    return 0;
}