vtable (_Main) { Main:
    main;
}

function (main) {
main:
    _T4 := 0
    _T3 := _T4
    _T5 := 0
    _T1 := _T5
    jmp _L8
_L9:
    _T6 := 1
    _T7 := _T1 + _T6
    _T1 := _T7
_L8:
    _T8 := 5
    _T9 := _T1 < _T8
    if (_T9 == 0) jmp _L10
    _T10 := 0
    _T2 := _T10
    jmp _L11
_L12:
    _T11 := 1
    _T12 := _T2 + _T11
    _T2 := _T12
_L11:
    _T13 := 5
    _T14 := _T2 < _T13
    if (_T14 == 0) jmp _L13
    _T15 := _T3 + _T2
    _T3 := _T15
    parm _T3
    call _PrintInt
    jmp _L12
_L13:
    jmp _L9
_L10:
}

