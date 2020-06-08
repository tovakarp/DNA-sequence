#ifndef __DNA_SEQ_H__
#define __DNA_SEQ_H__


#include <iostream>
#include <map>
#include <vector>
#include "cstring"
#include "string"

class dnaSequence{
private:
    class Nucleotide
    {
    public:
        Nucleotide(){};

        Nucleotide(char type);

        char getType() const;

        dnaSequence :: Nucleotide& operator=(char nucleotide);

        operator char(){
            return m_nucleotide;
        }
    private:
        bool isValidType(char nucleotide);
        char m_nucleotide; // Reference to the element to be modified
    };

public:
//    dnaSequence(const char *seq);
    dnaSequence(const std::string &seq);
    dnaSequence(const dnaSequence &seq);

    ~dnaSequence();

    dnaSequence& operator=(const dnaSequence&);
    dnaSequence& operator=(const std::string&);
//    dnaSequence& operator=(const char*);

    const Nucleotide& operator[](size_t i) const;
    Nucleotide& operator[](size_t index);
//
    const size_t length() const;

    dnaSequence slice(size_t start, size_t end) const;

    dnaSequence pairing() const;

    size_t find(const dnaSequence &subseq, size_t start = 0) const;

    std::vector<size_t> findAll(const dnaSequence &subseq, size_t start = 0) const;

    size_t count(const dnaSequence &subseq) const;

    std::vector<dnaSequence> findConsensus() const;

    friend std::ostream& operator << (std::ostream &os, dnaSequence &dna);

private:
    void initSeq(const char *seq);
    const dnaSequence::Nucleotide& getNucleotideByIndex(size_t index) const ;
    void initAssignment(const Nucleotide *seq, size_t length);

    Nucleotide *m_seq;
    size_t m_len;
};

//Nucleotide
inline dnaSequence::Nucleotide::Nucleotide(char type) : m_nucleotide(type){
    if(!isValidType(m_nucleotide))
        throw std::out_of_range ("*INVALID* type");
}

inline char dnaSequence::Nucleotide::getType() const {
    return m_nucleotide;
}

inline dnaSequence::Nucleotide& dnaSequence::Nucleotide::operator=(char nucleotide){
    if(isValidType(nucleotide)){
        m_nucleotide = nucleotide;
    }
    else {
        throw std::out_of_range ("*INVALID* Base");
    }
    return *this;
}

inline bool dnaSequence::Nucleotide::isValidType(char type){
    return type == 'A' || type == 'C' || type == 'G' || type == 'T';
}



//dnaSequence

inline dnaSequence::dnaSequence(const std::string &seq) : m_seq(NULL){
    initSeq(seq.c_str());
}

inline dnaSequence::dnaSequence(const dnaSequence &seq) : m_seq(NULL){
    m_len = seq.m_len;
    m_seq = new Nucleotide[m_len];
    for(size_t i = 0; i < m_len; ++i)
        m_seq[i] = seq.m_seq[i];
}

/*Dtor*/
inline dnaSequence::~dnaSequence() {
    delete [] m_seq;
    m_seq = NULL;
}

inline std::ostream& operator << (std::ostream &os, dnaSequence &dna){
    for(size_t i = 0; i < dna.m_len; ++i)
        os << dna.m_seq[i];
    os << std::endl;
    return os;
}

inline const size_t dnaSequence :: length() const{
    return m_len;
}

///*Operators*/
inline dnaSequence&  dnaSequence :: operator=(const dnaSequence &seq){

    try{
        Nucleotide *tmpSeq = new Nucleotide[seq.m_len];

        for(size_t i = 0; i < seq.m_len; ++i){
            tmpSeq[i] = seq.m_seq[i];
        }

        delete[] m_seq;

        m_len = seq.m_len;
        m_seq = tmpSeq;
    }
    catch (std::bad_alloc &ex) {
        std::cout << "Assignment operator unused" << std::endl;
    }
    return *this;
}

inline dnaSequence& dnaSequence::operator=(const std::string &seq){
    Nucleotide *tmpSeq;
    try{
        tmpSeq = new Nucleotide[seq.length()];

        for(size_t i = 0; i < seq.length(); ++i){
            tmpSeq[i] = seq[i];
        }

        delete[] m_seq;
        m_len = seq.length();
        m_seq = tmpSeq;
    }
    catch (std::bad_alloc &ex) {

        std::cout << "Assignment operator unused" << std::endl;
    }
    catch (std::out_of_range &ex) {
        delete [] tmpSeq;
        throw;
    }
    return *this;
}

inline bool operator==(const dnaSequence &dna1, const dnaSequence &dna2){
    if(dna1.length() != dna2.length())
        return false;

    for(size_t i = 0; i < dna1.length(); ++i){
        if(dna1[i].getType() != dna2[i].getType())
            return false;
    }

    return true;
}

inline bool operator!=(const dnaSequence &dna1, const dnaSequence &dna2){
    return !(dna1 == dna2);
}

inline const dnaSequence::Nucleotide& dnaSequence::getNucleotideByIndex(size_t index) const{
    if(index >= m_len)
        throw std::out_of_range("Index is out of range\n");

    return m_seq[index];
}

inline const dnaSequence::Nucleotide& dnaSequence::operator[](size_t index) const{
    return getNucleotideByIndex(index);
}

inline dnaSequence::Nucleotide& dnaSequence :: operator[](size_t index){
    return m_seq[index];
}

inline dnaSequence dnaSequence::slice(size_t start, size_t end) const{
    if(end >= m_len)
        throw std::out_of_range("Index is out of range");

    std::string s;

    size_t i, j;
    for(i = start, j = 0; i <= end; ++i , ++j){
        s += m_seq[i];
    }

    dnaSequence d(s);

    return d;
}

inline dnaSequence dnaSequence::pairing() const{
    std::map <char, char> pairs;
    pairs['A'] = 'T';
    pairs['T'] = 'A';
    pairs['C'] = 'G';
    pairs['G'] = 'C';

    std::string s;

    for(size_t i = 0; i < m_len; i++) {
        s += pairs[m_seq[m_len - i - 1]];
    }

    dnaSequence d(s);

    return d;
}

inline size_t dnaSequence::find(const dnaSequence &subseq, size_t start) const{
    size_t j;
    for(size_t i = start; i < m_len; ++i){
        if(m_seq[i] == subseq[0].getType()){
            for(j = 1; j < subseq.m_len; ++j){
                if(m_seq[i + j] != subseq[j].getType())
                    break;
            }
            if(subseq.m_len == j)
                return i;
        }
    }
    return -1;
}

inline std::vector<size_t> dnaSequence::findAll(const dnaSequence &subseq, size_t start) const{
    std::vector <size_t> indexVec;
    size_t currentIndex = start, index;

    while(currentIndex < m_len){
        index = find(subseq, currentIndex);

        if(index < m_len) {
            indexVec.push_back(index);
            currentIndex = index;
        }

        ++currentIndex;
    }

    return indexVec;
}

inline size_t dnaSequence::count(const dnaSequence &subseq) const{
    return findAll(subseq).size();
}

inline std::vector<dnaSequence> dnaSequence::findConsensus() const{
    std::vector<dnaSequence> consensus;
//    dnaSequence start("ATG");
//    std::vector<size_t> s_index = findAll(start);
//    size_t i = 0, index = 0;
//
//    for(i = 0; i < count(start); ++i){
//    }
    return consensus;
}


#endif