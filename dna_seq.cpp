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


void dnaSequence :: initAssignment(const Nucleotide *seq, size_t length){
    try{
        Nucleotide *tmpSeq = new Nucleotide[length];

        for(size_t i = 0; i < m_len; ++i){
            tmpSeq[i] = seq[i];
        }

        delete[] m_seq;
        m_seq = tmpSeq;
    }
    catch (std::bad_alloc &ex) {
        std::cout << "Assignment operator unused" << std::endl;
    }
}


//dnaSequence pairing(const dnaSequence &dna){
//    size_t len = dna.length();
//
//    std::map <char, char> pairs;
//    pairs['A'] = 'T';
//    pairs['T'] = 'A';
//    pairs['C'] = 'G';
//    pairs['G'] = 'C';
//
//    char *tmp = new char[len + 1];
//
//    tmp[len] = '\0';
////    char* str = dna.getSeq();
//
//    for(size_t i = 0; i<len; i++) {
//        tmp[i] = pairs[(dna.getSeq())[len - i +1].getType()];
//    }
//
//    dnaSequence new_dna(tmp);
//    delete[] tmp;
//    return new_dna;
//
//}
