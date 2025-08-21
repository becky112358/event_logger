#pragma once

template <typename IndexType, size_t N> 
const char* TcGetText(const char* (&sText)[N], IndexType nIdx)
{
	const size_t MaxIdx = N - 1;
	return (static_cast<size_t>(nIdx) > MaxIdx) ? sText[MaxIdx] : sText[static_cast<size_t>(nIdx)];
}
