#include <iostream>
#include <gtest/gtest.h>

#include "dna_seq.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(DnaBasicTests, InvalidType)
{
    ASSERT_THROW(dnaSequence a("ATF"), std::out_of_range);
    dnaSequence a("ATG");
    ASSERT_EQ(a, "ATG");
}

TEST(DnaBasicTests, Init){
    std::string  s = "ATCGAAT";
    dnaSequence a("ATCGAATGGC"), b(s), c(b);
    ASSERT_EQ(a,"ATCGAATGGC");
    ASSERT_EQ(b, s);
    ASSERT_EQ(b,c);
//    ASSERT_THROW(dnaSequence d);
}

TEST(DnaBasicTests, Length) {
    dnaSequence d("AAAAAAAAAAAAAAAAAAAC"), dd("");
    ASSERT_EQ(d.length(), 20);
    ASSERT_EQ(dd.length(), 0);
}

TEST(DnaBasicTests, Equality) {
    dnaSequence d("");
    d = "ATCG";
    ASSERT_EQ(d, "ATCG");

    d = d;
    ASSERT_EQ(d, "ATCG");

    ASSERT_THROW(d = "ATCH", std::out_of_range);
}

TEST(DnaBasicTests, Comparison){
    dnaSequence d("AAT"), dd("TTA");

    ASSERT_FALSE(d == dd);
    ASSERT_TRUE(d != dd);

    ASSERT_TRUE(dd == "TTA");
}

TEST(DnaBasicTests, Operator){
    dnaSequence d("AAAATTCCCGGG");

    ASSERT_EQ(d[5].getType(), 'T');

    d[3] = 'T';
    ASSERT_EQ(d, "AAATTTCCCGGG");

    ASSERT_THROW(d[8] = 'F', std::out_of_range);
}

TEST(DnaAdvancedTests, Slice)
{
    dnaSequence dna("AAAACCCCGGGG");
    ASSERT_EQ(dna.slice(2,9), "AACCCCGG");
    ASSERT_THROW(dna.slice(1, dna.length()), std::out_of_range);
}

TEST(DnaAdvancedTests, Pairing)
{
    dnaSequence d("ACGAT");
    ASSERT_EQ(d.pairing(), "ATCGT");
}

TEST(DnaAdvancedTests, Find)
{
    dnaSequence d("ACGACTCCT"), tsub("AC"), fsub("CA");
    ASSERT_TRUE(d.find(tsub) < d.length());
    ASSERT_FALSE(d.find(fsub) < d.length());
}

TEST(DnaAdvancedTests, FindAll)
{
    dnaSequence d("ACGACTCCT"), tsub("AC"), fsub("CA");
    ASSERT_EQ(d.findAll(tsub).size() ,2);
    ASSERT_FALSE(d.findAll(fsub).size() == 2);
}

TEST(DnaAdvancedTests, FindConsensus)
{
    dnaSequence dna1("AAAAATGACCGACTAAATGTAG"), dna2("ATTTTTTTTTTCCCCCCCCCGA");
    std::vector<dnaSequence> d = dna1.findConsensus();

    ASSERT_EQ(d[1],"ATGACCGACTAAATGTAG");

    ASSERT_EQ(dna1.findConsensus().size() ,3);
    ASSERT_EQ(dna2.findConsensus().size(), 0);
}

TEST(DnaAdvancedTests, WriteToFile){
    dnaSequence d("ATG");
    d.writeDNAToFile("dna.txt");

    std::ifstream filePtr;
    filePtr.open("dna.txt");

    std::string dnaSequence;
    std::string line;

    getline(filePtr, line);

    ASSERT_EQ(d, line);
}


TEST(DnaAdvancedTests, ReadFromFile){
    dnaSequence d("");
    d.readDNAFromFile("dna.txt");

    ASSERT_EQ(d, "ATG");
}