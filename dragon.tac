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

vtable (_Main) { Main:
    main;
}

function (_Computer_New) {
_Computer_New:
    _T14 := 8
    parm _T14
    _T15 :=  call malloc
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
    _T19 :=  call malloc
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
    _T23 :=  call malloc
    _T24 := 0
    *(_T23 + 4) := _T24
    *(_T23 + 8) := _T24
    _T25 := VTBL <_OSX>
    *(_T23 + 0) := _T25
    return _T23
}

function (_Expression_New) {
_Expression_New:
    _T26 := 12
    parm _T26
    _T27 :=  call malloc
    _T28 := 0
    *(_T27 + 4) := _T28
    *(_T27 + 8) := _T28
    _T29 := VTBL <_Expression>
    *(_T27 + 0) := _T29
    return _T27
}

function (_Function_New) {
_Function_New:
    _T30 := 8
    parm _T30
    _T31 :=  call malloc
    _T32 := 0
    *(_T31 + 4) := _T32
    _T33 := VTBL <_Function>
    *(_T31 + 0) := _T33
    return _T31
}

function (_Statement_New) {
_Statement_New:
    _T34 := 4
    parm _T34
    _T35 :=  call malloc
    _T36 := VTBL <_Statement>
    *(_T35 + 0) := _T36
    return _T35
}

function (_Variable_New) {
_Variable_New:
    _T37 := 8
    parm _T37
    _T38 :=  call malloc
    _T39 := 0
    *(_T38 + 4) := _T39
    _T40 := VTBL <_Variable>
    *(_T38 + 0) := _T40
    return _T38
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
    _T41 := *(_T3 + 8)
    _T42 := *(_T3 + 4)
    *(_T3 + 8) := _T42
    _T43 := *(_T3 + 4)
    *(_T3 + 4) := _T4
    _T44 := LOADHello Mac!
    parm _T44
    call _PrintString
    _T45 := *(_T3 + 4)
    parm _T45
    call _PrintInt
    _T46 := 1
    _T47 := _T4 + _T46
    return _T47
}

function (_OSX.superSuperField) {
_OSX.superSuperField:
    _T48 := *(_T5 + 4)
    return _T48
}

function (_Expression.main) {
_Expression.main:
    _T49 := *(_T6 + 4)
    _T50 := 1
    _T51 := 4
    _T52 := _T50 * _T51
    _T53 := _T49 + _T52
    _T54 := *(_T53 + 0)
    _T55 := 1
    _T56 := 4
    _T57 := _T50 * _T56
    _T58 := _T49 + _T57
    *(_T58 + 0) := _T55
    _T59 := *(_T6 + 4)
    _T60 := 2
    _T61 := 4
    _T62 := _T60 * _T61
    _T63 := _T59 + _T62
    _T64 := *(_T63 + 0)
    _T65 := *(_T6 + 4)
    _T66 := 0
    _T67 := 4
    _T68 := _T66 * _T67
    _T69 := _T65 + _T68
    _T70 := *(_T69 + 0)
    _T71 := *(_T6 + 4)
    _T72 := 1
    _T73 := 4
    _T74 := _T72 * _T73
    _T75 := _T71 + _T74
    _T76 := *(_T75 + 0)
    _T77 := _T70 || _T76
    _T78 := 4
    _T79 := _T60 * _T78
    _T80 := _T59 + _T79
    *(_T80 + 0) := _T77
    _T81 := *(_T6 + 8)
    _T82 := 1
    _T83 := 4
    _T84 := _T82 * _T83
    _T85 := _T81 + _T84
    _T86 := *(_T85 + 0)
    _T87 := 233
    _T88 := 4
    _T89 := _T82 * _T88
    _T90 := _T81 + _T89
    *(_T90 + 0) := _T87
    _T91 := *(_T6 + 8)
    _T92 := 2
    _T93 := 4
    _T94 := _T92 * _T93
    _T95 := _T91 + _T94
    _T96 := *(_T95 + 0)
    _T97 := *(_T6 + 8)
    _T98 := 1
    _T99 := 4
    _T100 := _T98 * _T99
    _T101 := _T97 + _T100
    _T102 := *(_T101 + 0)
    _T103 := *(_T6 + 8)
    _T104 := 0
    _T105 := 4
    _T106 := _T104 * _T105
    _T107 := _T103 + _T106
    _T108 := *(_T107 + 0)
    _T109 := _T102 + _T108
    _T110 := 4
    _T111 := _T92 * _T110
    _T112 := _T91 + _T111
    *(_T112 + 0) := _T109
    _T114 := *(_T6 + 8)
    _T115 := 0
    _T116 := 4
    _T117 := _T115 * _T116
    _T118 := _T114 + _T117
    _T119 := *(_T118 + 0)
    _T120 := - _T119
    _T113 := _T120
    _T122 := *(_T6 + 4)
    _T123 := 2
    _T124 := 4
    _T125 := _T123 * _T124
    _T126 := _T122 + _T125
    _T127 := *(_T126 + 0)
    _T128 := ! _T127
    _T121 := _T128
    _T133 := 3
    _T129 := _T133
    _T134 := 4
    _T130 := _T134
    _T135 := 3
    _T136 := 4
    _T137 := 7
    _T131 := _T137
    _T138 := _T129 * _T130
    _T131 := _T138
    _T139 := 5
    _T140 := _T131 / _T139
    _T132 := _T140
}

function (_Function.funcTest) {
_Function.funcTest:
    _T141 := LOADFuncTest:
    parm _T141
    call _PrintString
    parm _T8
    call _PrintInt
    return _T8
}

function (_Function.errorRetType) {
_Function.errorRetType:
    _T142 := 1
    return _T142
}

function (_Statement.stmt2) {
_Statement.stmt2:
_L23:
    _T144 := 0
    _T145 := _T143 > _T144
    if (_T145 == 0) jmp _L24
    _T147 := 1
    _T148 := _T143 - _T147
    _T143 := _T148
    _T149 := 1
    _T150 := _T143 - _T149
    _T146 := _T150
    jmp _L23
_L24:
_L25:
    _T151 := 0
    _T152 := _T143 < _T151
    if (_T152 == 0) jmp _L26
    _T154 := 1
    _T155 := _T153 - _T154
    _T153 := _T155
    _T156 := 1
    _T157 := _T143 + _T156
    _T143 := _T157
    jmp _L25
_L26:
    _T158 := 0
    _T143 := _T158
    jmp _L27
_L28:
    _T159 := 1
    _T160 := _T143 + _T159
    _T143 := _T160
_L27:
    _T161 := 10
    _T162 := _T143 < _T161
    if (_T162 == 0) jmp _L29
    parm _T143
    call _PrintInt
    jmp _L28
_L29:
}

function (_Variable.varTest) {
_Variable.varTest:
    _T163 := *(_T12 + 4)
    _T164 := 5
    _T165 := 4
    _T166 := _T165 * _T164
    _T167 := _T165 + _T166
    parm _T167
    _T168 :=  call malloc
    *(_T168 + 0) := _T164
    _T169 := 0
    _T168 := _T168 + _T167
_L30:
    _T167 := _T167 - _T165
    if (_T167 == 0) jmp _L31
    _T168 := _T168 - _T165
    *(_T168 + 0) := _T169
    jmp _L30
_L31:
    *(_T12 + 4) := _T168
    _T170 := *(_T12 + 4)
    _T171 := 1
    _T172 := 4
    _T173 := _T171 * _T172
    _T174 := _T170 + _T173
    _T175 := *(_T174 + 0)
    _T176 := 1
    _T177 := 4
    _T178 := _T176 * _T177
    _T179 := _T175 + _T178
    _T180 := *(_T179 + 0)
    return _T180
}

function (main) {
main:
    _T182 := 1
    _T181 := _T182
    _T184 :=  call _Mac_New
    _T183 := _T184
    _T185 := 2
    parm _T185
    parm _T183
    _T186 := *(_T183 + 0)
    _T187 := *(_T186 + 8)
    _T188 :=  call _T187
    parm _T183
    _T189 := *(_T183 + 0)
    _T190 := *(_T189 + 12)
    call _T190
    _T192 :=  call _Function_New
    _T191 := _T192
    _T193 := 3
    _T194 := _T181 * _T193
    parm _T194
    parm _T191
    _T195 := *(_T191 + 0)
    _T196 := *(_T195 + 12)
    _T197 :=  call _T196
}

