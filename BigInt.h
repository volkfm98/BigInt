#ifndef BIGINT_H_

#define BIGINT_H_

const long long MAX_CHUNK_VALUE = 1e9;
const long long MAX_DIGIT_COUNT = 9;

class BigIntChunk {
	friend class BigInt;

	private:
	BigIntChunk *next, *prev;
	long long val;

	int digitCount();

	public:
	BigIntChunk();
	BigIntChunk(const long long &a);

	BigIntChunk operator= (const BigIntChunk &b);
	BigIntChunk operator= (const long long &b);

	long long operator+ (const BigIntChunk &b);
	void addRemainder(const long long &b);
	//No need in some operators for this task, but want implement it later for fun
	//TODO: Implement minus_operators
	//void operator- ();
	//long long operator- (BigIntChunk b);
	long long operator* (const BigIntChunk &b);
	//TODO: Implement division_operator

	void write();
};

class BigInt {
	public:
	BigIntChunk *begin, *end;

	void extend();

	public:
	BigInt();
	BigInt(const long long &a);

	BigInt operator= (const BigInt &b);
	BigInt operator= (const long long &b);

	BigInt operator+ (const BigInt &b);
	//BigInt operator- (BigInt b);
	BigInt operator* (const BigInt &b);

	//void read();
	void write();

	~BigInt();
};

#endif
