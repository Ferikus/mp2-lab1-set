// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int _BitLen)
{
	if (_BitLen <= 0) throw "Wrong length in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	else {
		MemLen = _BitLen / 32 + 1;
		pMem = new TELEM[MemLen];
		BitLen = _BitLen;
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n <= 0 || n >= BitLen) throw "Wrong index in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n <= 0 || n >= BitLen) throw "Wrong index in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	return 1 << (n % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n <= 0 || n >= BitLen) throw "Wrong index in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	TELEM mask = GetMemMask(n);
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n <= 0 || n >= BitLen) throw "Wrong index in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	TELEM mask = ~GetMemMask(n);
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n <= 0 || n >= BitLen) throw "Wrong index in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	TELEM mask = GetMemMask(n);
	int idx = GetMemIndex(n);
	TELEM res = mask & pMem[idx];
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf.MemLen != MemLen) {
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return false;
	for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i]) return false;
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i)) return false;
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxLen = bf.BitLen;
	if (BitLen > bf.BitLen) maxLen = BitLen;
	if (BitLen < maxLen)
		for (int i = BitLen; i < MemLen * 32; i++) pMem[i] = 0;
	else
		for (int i = bf.BitLen; i < bf.MemLen * 32; i++) bf.pMem[i] = 0;
	TBitField res(maxLen);
	for (int i = 0; i < maxLen; i++)
		res.pMem[i] = pMem[i] | bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxLen = bf.BitLen;
	if (BitLen > bf.BitLen) maxLen = BitLen;
	if (BitLen < maxLen)
		for (int i = BitLen; i < MemLen * 32; i++) pMem[i] = 0;
	else
		for (int i = bf.BitLen; i < bf.MemLen * 32; i++) bf.pMem[i] = 0;
	TBitField res(maxLen);
	for (int i = 0; i < maxLen; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = ~pMem[i];
	return res;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
	char num;
	for (int i = 0; i < bf.BitLen; i++) bf.pMem[i] = 0;
	for (int i = 0; i < bf.BitLen; i++)
	{
		is >> num;
		if (num == '1') bf.SetBit(i);
		else if (num == '0') bf.ClrBit(i);
		else break;
	}
	return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		bf.GetBit(i) ? os << '1' : os << '0';
	return os;
}
