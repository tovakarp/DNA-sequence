#include "dna_seq.h"

void dnaSequence :: initSeq(const char *seq){
    m_seq = new char[strlen(seq) + 1];
    strcpy(m_seq,seq);
}

void dnaSequence :: initAssignment(const char *seq){
    if(!strcmp(m_seq, seq))
        return;
    try{
        char *tmpSeq = new char[strlen(seq) + 1];
        delete[] m_seq;
        m_seq = tmpSeq;
        strcpy(m_seq, seq);
    }

    catch (std::bad_alloc &ex) {
        std::cout << "Assignment operator unused" << std::endl;
    }
}
