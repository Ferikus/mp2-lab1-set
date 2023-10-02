// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int _BitLen)
{
	if (BitLen <= 0) throw "Wrong length in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	else {
		MemLen = _BitLen / 32 + 1;
		pMem = new TELEM[MemLen];
		BitLen = _BitLen;
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (bf.BitLen <= 0) throw "Wrong length in file", __FILE__, ", function", __FUNCTION__, ", line", __LINE__;
	else {
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		BitLen = bf.BitLen;
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
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
	return*this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return* this;
}

TBitField TBitField::operator~(void) // отрицание
{
	return*this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;

}
