//#include <map>
#include "dna_seq.h"

void dnaSequence :: initSeq(const char *seq){
    try{
        m_len = strlen(seq);
        m_seq = new Nucleotide[strlen(seq)];

        for(size_t i = 0; i < m_len; ++i){
            m_seq[i] = seq[i];
        }
    }
    catch (std::out_of_range &ex) {
        std::cout << ex.what() << std::endl;
        throw;
    }
}

