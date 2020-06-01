#ifndef __DNA_SEQ_H__
#define __DNA_SEQ_H__


#include <iostream>
#include "cstring"
#include "string"

class dnaSequence{
public:
    dnaSequence(const char *seq);
    dnaSequence(const std::string &seq);
    dnaSequence(const dnaSequence &seq);
    ~dnaSequence();

    dnaSequence& operator=(const dnaSequence&);
    dnaSequence& operator=(const std::string&);
    dnaSequence& operator=(const char*);

    char operator[](unsigned int i) const;

    const size_t length();

    const char* getSeq() const;

    friend std::ostream& operator << (std::ostream &os, dnaSequence &dna);

private:
    void initSeq(const char *seq);
    void initAssignment(const char *seq);
    char *m_seq;
};

inline bool operator==(const dnaSequence &dna1, const dnaSequence &dna2){
    return !strcmp(dna1.getSeq(), dna2.getSeq());
}

inline bool operator!=(const dnaSequence &dna1, const dnaSequence &dna2){
    return !(dna1 == dna2);
}

/*Constractors*/
inline dnaSequence::dnaSequence(const char *seq) : m_seq(NULL){
    initSeq(seq);
}

inline dnaSequence::dnaSequence(const std::string &seq) : m_seq(NULL){
    initSeq(seq.c_str());
}

inline dnaSequence::dnaSequence(const dnaSequence &seq) : m_seq(NULL){
    initSeq(seq.m_seq);
}

/*Dtor*/
inline dnaSequence::~dnaSequence() {
    delete [] m_seq;
    m_seq = NULL;
}

inline std::ostream& operator << (std::ostream &os, dnaSequence &dna){
    os << dna.m_seq << std::endl;
    return os;
}

inline const char* dnaSequence :: getSeq() const {
    return m_seq;
}

inline const size_t dnaSequence :: length(){
    return strlen(m_seq);
}

/*Operators*/
inline dnaSequence&  dnaSequence :: operator=(const dnaSequence &seq){
    initAssignment(seq.m_seq);
    return *this;
}

inline dnaSequence& dnaSequence::operator=(const char *seq){
    initAssignment(seq);
    return *this;
}

inline dnaSequence& dnaSequence::operator=(const std::string &seq){
    initAssignment(seq.c_str());
    return *this;
}

inline char dnaSequence::operator[](unsigned int i) const{
    if( i <= strlen(m_seq))
        return m_seq[i];
    throw std::out_of_range ("*BAD* Index");
}

#endif