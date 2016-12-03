vtable (_Computer) { Computer:
    _Computer.crash;
    _Computer.superMethod;
}

vtable (_Mac) { Mac:_Computer
    _Mac.crash;
    _Computer.superMethod;
}

vtable (_OSX) { OSX:_Mac
    _Mac.crash;
    _Computer.superMethod;
    _OSX.superSuperField;
}

vtable (_Main) { Main:
    main;
}

vtable (_Expression) { Expression:
    _Expression.main;
}

vtable (_Function) { Function:
    _Function.errorRetType;
    _Function.funcTest;
}

vtable (_Statement) { Statement:
    _Statement.stmt2;
}

vtable (_Variable) { Variable:
    _Variable.varTest;
}

function (_Computer_New) {
_Computer_New:
    _T14 := 8
    parm _T14
    _T15 :=  call _Alloc
    _T16 := 0
    *(_T15 + 4) := _T16
    _T17 := VTBL <_Computer>
    *(_T15 + 0) := _T17
    return _T15
}

function (_Mac_New) {
_Mac_New:
    _T18 := 12
    parm _T18
    _T19 :=  call _Alloc
    _T20 := 0
    *(_T19 + 4) := _T20
    *(_T19 + 8) := _T20
    _T21 := VTBL <_Mac>
    *(_T19 + 0) := _T21
    return _T19
}

function (_OSX_New) {
_OSX_New:
    _T22 := 12
    parm _T22
    _T23 :=  call _Alloc
    _T24 := 0
    *(_T23 + 4) := _T24
    *(_T23 + 8) := _T24
    _T25 := VTBL <_OSX>
    *(_T23 + 0) := _T25
    return _T23
}

function (_Main_New) {
_Main_New:
    _T26 := 8
    parm _T26
    _T27 :=  call _Alloc
    _T28 := 0
    *(_T27 + 4) := _T28
    _T29 := VTBL <_Main>
    *(_T27 + 0) := _T29
    return _T27
}

function (_Expression_New) {
_Expression_New:
    _T30 := 12
    parm _T30
    _T31 :=  call _Alloc
    _T32 := 0
    *(_T31 + 4) := _T32
    *(_T31 + 8) := _T32
    _T33 := VTBL <_Expression>
    *(_T31 + 0) := _T33
    return _T31
}

function (_Function_New) {
_Function_New:
    _T34 := 8
    parm _T34
    _T35 :=  call _Alloc
    _T36 := 0
    *(_T35 + 4) := _T36
    _T37 := VTBL <_Function>
    *(_T35 + 0) := _T37
    return _T35
}

function (_Statement_New) {
_Statement_New:
    _T38 := 4
    parm _T38
    _T39 :=  call _Alloc
    _T40 := VTBL <_Statement>
    *(_T39 + 0) := _T40
    return _T39
}

function (_Variable_New) {
_Variable_New:
    _T41 := 8
    parm _T41
    _T42 :=  call _Alloc
    _T43 := 0
    *(_T42 + 4) := _T43
    _T44 := VTBL <_Variable>
    *(_T42 + 0) := _T44
    return _T42
}

function (_Computer.crash) {
_Computer.crash:
    parm _T1
    call _PrintInt
    return _T1
}

function (_Computer.superMethod) {
_Computer.superMethod:
    return <empty>
}

function (_Mac.crash) {
_Mac.crash:
    _T45 := *(_T3 + 8)
    _T46 := *(_T3 + 4)
    *(_T3 + 8) := _T46
    _T47 := *(_T3 + 4)
    *(_T3 + 4) := _T4
    _T48 := ack!
    parm _T48
    call _PrintString
    _T49 := 1
    _T50 := _T4 + _T49
    return _T50
}

function (_OSX.superSuperField) {
_OSX.superSuperField:
    _T51 := *(_T5 + 4)
    return _T51
}

function (main) {
main:
    _T53 := *(_T6 + 4)
    _T52 := _T53
    _T55 :=  call _Mac_New
    _T54 := _T55
    _T56 := 2
    parm _T54
    parm _T56
    _T57 := *(_T54 + 0)
    _T58 := *(_T57 + 8)
    _T59 :=  call _T58
    parm _T54
    _T60 := *(_T54 + 0)
    _T61 := *(_T60 + 12)
    call _T61
}

function (_Expression.main) {
_Expression.main:
    _T62 := *(_T7 + 4)
    _T63 := 1
    _T64 := 4
    _T65 := _T63 * _T64
    _T66 := _T62 + _T65
    _T67 := *(_T66 + 0)
    _T68 := 1
    _T69 := 4
    _T70 := _T63 * _T69
    _T71 := _T62 + _T70
    *(_T71 + 0) := _T68
    _T72 := *(_T7 + 4)
    _T73 := 2
    _T74 := 4
    _T75 := _T73 * _T74
    _T76 := _T72 + _T75
    _T77 := *(_T76 + 0)
    _T78 := *(_T7 + 4)
    _T79 := 0
    _T80 := 4
    _T81 := _T79 * _T80
    _T82 := _T78 + _T81
    _T83 := *(_T82 + 0)
    _T84 := *(_T7 + 4)
    _T85 := 1
    _T86 := 4
    _T87 := _T85 * _T86
    _T88 := _T84 + _T87
    _T89 := *(_T88 + 0)
    _T90 := _T83 || _T89
    _T91 := 4
    _T92 := _T73 * _T91
    _T93 := _T72 + _T92
    *(_T93 + 0) := _T90
    _T94 := *(_T7 + 8)
    _T95 := 1
    _T96 := 4
    _T97 := _T95 * _T96
    _T98 := _T94 + _T97
    _T99 := *(_T98 + 0)
    _T100 := 233
    _T101 := 4
    _T102 := _T95 * _T101
    _T103 := _T94 + _T102
    *(_T103 + 0) := _T100
    _T104 := *(_T7 + 8)
    _T105 := 2
    _T106 := 4
    _T107 := _T105 * _T106
    _T108 := _T104 + _T107
    _T109 := *(_T108 + 0)
    _T110 := *(_T7 + 8)
    _T111 := 1
    _T112 := 4
    _T113 := _T111 * _T112
    _T114 := _T110 + _T113
    _T115 := *(_T114 + 0)
    _T116 := *(_T7 + 8)
    _T117 := 0
    _T118 := 4
    _T119 := _T117 * _T118
    _T120 := _T116 + _T119
    _T121 := *(_T120 + 0)
    _T122 := _T115 + _T121
    _T123 := 4
    _T124 := _T105 * _T123
    _T125 := _T104 + _T124
    *(_T125 + 0) := _T122
    _T127 := *(_T7 + 8)
    _T128 := 0
    _T129 := 4
    _T130 := _T128 * _T129
    _T131 := _T127 + _T130
    _T132 := *(_T131 + 0)
    _T133 := - _T132
    _T126 := _T133
    _T135 := *(_T7 + 4)
    _T136 := 2
    _T137 := 4
    _T138 := _T136 * _T137
    _T139 := _T135 + _T138
    _T140 := *(_T139 + 0)
    _T141 := ! _T140
    _T134 := _T141
    _T146 := 3
    _T142 := _T146
    _T147 := 4
    _T143 := _T147
    _T148 := 3
    _T149 := 4
    _T150 := 7
    _T144 := _T150
    _T151 := 12
    _T144 := _T151
    _T152 := 5
    _T153 := 2
    _T145 := _T153
}

function (_Function.funcTest) {
_Function.funcTest:
    _T154 := 1
    _T9 := _T154
    return _T9
}

function (_Function.errorRetType) {
_Function.errorRetType:
    _T155 := 1
    return _T155
}

function (_Statement.stmt2) {
_Statement.stmt2:
_L25:
    _T157 := 0
    _T158 := _T156 > _T157
    if (_T158 == 0) jmp _L26
    _T160 := 1
    _T161 := _T156 - _T160
    _T156 := _T161
    _T162 := 1
    _T163 := _T156 - _T162
    _T159 := _T163
    jmp _L25
_L26:
_L27:
    _T164 := 0
    _T165 := _T156 < _T164
    if (_T165 == 0) jmp _L28
    _T167 := 1
    _T168 := _T166 - _T167
    _T166 := _T168
    _T169 := 1
    _T170 := _T156 + _T169
    _T156 := _T170
    jmp _L27
_L28:
    _T171 := 0
    _T156 := _T171
    jmp _L29
_L30:
    _T172 := 1
    _T173 := 1
    _T156 := _T173
_L29:
    _T174 := 10
    _T175 := 1
    if (_T175 == 0) jmp _L31
    parm _T156
    call _PrintInt
    jmp _L30
_L31:
}

function (_Variable.varTest) {
_Variable.varTest:
    _T176 := *(_T13 + 4)
    _T177 := 5
    _T178 := 4
    _T179 := _T178 * _T177
    _T180 := _T178 + _T179
    parm _T180
    _T181 :=  call _Alloc
    *(_T181 + 0) := _T177
    _T182 := 0
    _T181 := _T181 + _T180
_L32:
    _T180 := _T180 - _T178
    if (_T180 == 0) jmp _L33
    _T181 := _T181 - _T178
    *(_T181 + 0) := _T182
    jmp _L32
_L33:
    *(_T13 + 4) := _T181
    _T183 := *(_T13 + 4)
    _T184 := 1
    _T185 := 4
    _T186 := _T184 * _T185
    _T187 := _T183 + _T186
    _T188 := *(_T187 + 0)
    _T189 := 1
    _T190 := 4
    _T191 := _T189 * _T190
    _T192 := _T188 + _T191
    _T193 := *(_T192 + 0)
    return _T193
}

