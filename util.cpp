#include "util.h"
#include <filesystem>

void error(std::string message)
{
    std::cerr << "ERROR: " << message << std::endl;
    exit(1);
}

IStreamWrapper::IStreamWrapper(std::string filename) : filename(filename), 
    readfile(std::ifstream(filename, std::ios::binary)), buf(0), buf_index(8) {}

bool IStreamWrapper::good() const
{
    return readfile.good();
}

long unsigned int IStreamWrapper::size() const
{
    return std::filesystem::file_size(filename);
}

void IStreamWrapper::reset()
{
    readfile.clear(); //clear EOF
    readfile.seekg(0); //reset file reading
    buf = 0; //clear buffer
    buf_index = 8; //reset bitwise buffer index
}

unsigned long IStreamWrapper::readLong()
{
    if (buf_index != 8)
        error("Active bit buffer");
    unsigned long num;
    readfile.read((char*)&num, sizeof(num));
    if (readfile.eof())
        error("Not enough bytes to read long from file");
    return num;
}

unsigned int IStreamWrapper::readInt()
{
    if (buf_index != 8)
        error("Active bit buffer");
    unsigned int num;
    readfile.read((char*)&num, sizeof(num));
    if (readfile.eof())
        error("Not enough bytes to read int from file");
    return num;
}

int IStreamWrapper::readByte()
{
    return readfile.get();
}

unsigned char IStreamWrapper::readBit()
{
    if (buf_index == 8)
    {
        unsigned char temp = readByte();
        //if there are no more bytes to read,
        //return char(-1)
        if (temp == -1)
            return -1;
        buf = temp;
        buf_index = 0;
    }
    //return current bit
    return (buf >> (7 - buf_index++)) & 1;
}

OStreamWrapper::OStreamWrapper(std::string filename) : 
    writefile(std::ofstream(filename, std::ios::binary)), buf(0), buf_index(0) {}

bool OStreamWrapper::good() const
{
    return writefile.good();
}

void OStreamWrapper::writeLong(unsigned long l)
{
    if (buf_index)
        error("Active bit buffer");
    writefile.write((char*)&l, sizeof(l));
}

void OStreamWrapper::writeInt(unsigned int n)
{
    if (buf_index)
        error("Active bit buffer");
    writefile.write((char*)&n, sizeof(n));
}

void OStreamWrapper::writeByte(unsigned char b)
{
    if (buf_index)
        error("Active bit buffer");
    else
        writefile.put(b);
}

void OStreamWrapper::writeBit(unsigned char b)
{
    if (!(b == 0 || b == 1))
        error("Invalid bit");
    buf |= (b << (7-buf_index++));
    //write 8 bits (1 byte) at a time
    if (buf_index == 8)
        flush_bitwise();
}

void OStreamWrapper::flush_bitwise()
{
    if (buf_index)
    {
        writefile.put(buf);
        buf = 0;
        buf_index = 0;
    }
}

void OStreamWrapper::flush()
{
    flush_bitwise();
    writefile.flush();
}

OStreamWrapper::~OStreamWrapper()
{
    flush();
}

Node::Node(unsigned long int count, unsigned char symbol)
{
    this->count = count;
    this->symbol = symbol;
    this->l = nullptr;
    this->r = nullptr;
    this->p = nullptr;
}

bool Node::operator<(const Node& other)
{
    //compare counts
    if (count != other.count)
    {
        return count > other.count;
    }
    //compare symbols
    return symbol > other.symbol;
}

bool NodeComp::operator()(Node*& lhs, Node*& rhs)
{
    return *lhs < *rhs;
}