#pragma once
#include <algorithm>


// TODO: � ������ ����� ������ ���� ����������� ��������� ������� ��� ����������.
//       ��� � � ������ ��������� �������, ���������� ��������� ������� ������ ������� �� .h � .cpp �����.

//������� �������� ���������
template <typename _Pred, typename _Iter>
concept predConcept = requires(_Pred _p, _Iter _i) {
    {_p(*_i)} -> std::convertible_to<bool>; //!!! convertible_to
};
//������� ��������� ���������
template <typename _Iter, typename _Pred> concept predConceptBin = requires(_Iter _i1, _Iter _i2, _Pred _p) {
    {_p(*_i1, *_i2)} -> std::convertible_to<bool>;
};

//������� �������� � ������ �������
template <typename _Iter, typename _Func> concept funcConcept = requires( _Iter _i, _Func _f) {
    _f(_i);
};
//������� ���������
template <typename _Iter> concept iterConcept = requires(_Iter _i) {
    std::totally_ordered<_Iter>;
    {*_i} -> std::same_as<std::iter_reference_t<_Iter>>;
    {_i++} -> std::same_as<_Iter&>;
    {_i--} -> std::same_as<_Iter&>;
    {--_i} -> std::same_as<_Iter&>;
    {++_i} -> std::same_as<_Iter&>;
};
//����������� �������
template <typename _Iter>
requires iterConcept<_Iter>
_Iter min(_Iter beg_p, _Iter end_p) {
    _Iter tmp = beg_p;
    for (; beg_p != end_p; beg_p++) {
        if (*beg_p < *tmp) {
            tmp = beg_p;
        }
    }
    return tmp;
}

//������������ �������
template <typename _Iter>
requires iterConcept<_Iter>
_Iter max(_Iter beg_p, _Iter end_p) {
    _Iter tmp = beg_p;
    for (; beg_p != end_p; beg_p++) {
        if (*beg_p > *tmp) {
            tmp = beg_p;
        }
    }
    return tmp;
}
//foreach
template <typename _Iter, typename _Func>
requires iterConcept<_Iter> and funcConcept<_Iter, _Func>
void foreach(_Iter beg_p, _Iter end_p, _Func f_p) {
    for (; beg_p != end_p; beg_p++) {
        f_p(beg_p);
    }
}
//����� ������� ���������
template <typename _Iter, typename _Pred>
requires iterConcept<_Iter> and predConcept<_Pred, _Iter>
_Iter findIf(_Iter beg_p, _Iter end_p, _Pred p) {
    _Iter ans = end_p;
    for (; beg_p != end_p; beg_p++) {
        if (p(*beg_p)) {
            ans = beg_p;
            break;
        }
    }
    return ans;
}

//����������
template <typename _Iter, typename _Pred>
requires iterConcept<_Iter> and predConceptBin<_Iter, _Pred>
void sort(_Iter beg_p, _Iter end_p, _Pred p) {
    for (_Iter iter_f = beg_p; iter_f != end_p; ++iter_f) {
        for (_Iter iter_s = iter_f + 1; iter_s != end_p; ++iter_s) {
            if (!p(*iter_f, *iter_s)) {
                std::swap(*iter_f, *iter_s);
            }
        }
    }
}
//����������� �� �������
template <typename _IterS, typename _IterD, typename _Pred>
requires iterConcept<_IterS> and iterConcept<_IterD> and predConcept<_Pred, _IterS>
size_t copyIf(_IterS sourceBeg, _IterS sourceEnd, _IterD destBeg, _Pred p) {
    size_t n = 0;
    for (; sourceBeg != sourceEnd; ++sourceBeg) {
        if (p(*sourceBeg)) {
            n++;
            *destBeg = *sourceBeg;
            destBeg++;
        }
    }
    return n;
}