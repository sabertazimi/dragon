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
    _T44 := LOADack!
    parm _T44
    call _PrintString
    _T45 := 1
    _T46 := _T4 + _T45
    return _T46
}

function (_OSX.superSuperField) {
_OSX.superSuperField:
    _T47 := *(_T5 + 4)
    return _T47
}

function (_Expression.main) {
_Expression.main:
    _T48 := *(_T6 + 4)
    _T49 := 1
    _T50 := 4
    _T51 := _T49 * _T50
    _T52 := _T48 + _T51
    _T53 := *(_T52 + 0)
    _T54 := 1
    _T55 := 4
    _T56 := _T49 * _T55
    _T57 := _T48 + _T56
    *(_T57 + 0) := _T54
    _T58 := *(_T6 + 4)
    _T59 := 2
    _T60 := 4
    _T61 := _T59 * _T60
    _T62 := _T58 + _T61
    _T63 := *(_T62 + 0)
    _T64 := *(_T6 + 4)
    _T65 := 0
    _T66 := 4
    _T67 := _T65 * _T66
    _T68 := _T64 + _T67
    _T69 := *(_T68 + 0)
    _T70 := *(_T6 + 4)
    _T71 := 1
    _T72 := 4
    _T73 := _T71 * _T72
    _T74 := _T70 + _T73
    _T75 := *(_T74 + 0)
    _T76 := _T69 || _T75
    _T77 := 4
    _T78 := _T59 * _T77
    _T79 := _T58 + _T78
    *(_T79 + 0) := _T76
    _T80 := *(_T6 + 8)
    _T81 := 1
    _T82 := 4
    _T83 := _T81 * _T82
    _T84 := _T80 + _T83
    _T85 := *(_T84 + 0)
    _T86 := 233
    _T87 := 4
    _T88 := _T81 * _T87
    _T89 := _T80 + _T88
    *(_T89 + 0) := _T86
    _T90 := *(_T6 + 8)
    _T91 := 2
    _T92 := 4
    _T93 := _T91 * _T92
    _T94 := _T90 + _T93
    _T95 := *(_T94 + 0)
    _T96 := *(_T6 + 8)
    _T97 := 1
    _T98 := 4
    _T99 := _T97 * _T98
    _T100 := _T96 + _T99
    _T101 := *(_T100 + 0)
    _T102 := *(_T6 + 8)
    _T103 := 0
    _T104 := 4
    _T105 := _T103 * _T104
    _T106 := _T102 + _T105
    _T107 := *(_T106 + 0)
    _T108 := _T101 + _T107
    _T109 := 4
    _T110 := _T91 * _T109
    _T111 := _T90 + _T110
    *(_T111 + 0) := _T108
    _T113 := *(_T6 + 8)
    _T114 := 0
    _T115 := 4
    _T116 := _T114 * _T115
    _T117 := _T113 + _T116
    _T118 := *(_T117 + 0)
    _T119 := - _T118
    _T112 := _T119
    _T121 := *(_T6 + 4)
    _T122 := 2
    _T123 := 4
    _T124 := _T122 * _T123
    _T125 := _T121 + _T124
    _T126 := *(_T125 + 0)
    _T127 := ! _T126
    _T120 := _T127
    _T132 := 3
    _T128 := _T132
    _T133 := 4
    _T129 := _T133
    _T134 := 3
    _T135 := 4
    _T136 := 7
    _T130 := _T136
    _T137 := _T128 * _T129
    _T130 := _T137
    _T138 := 5
    _T139 := _T130 / _T138
    _T131 := _T139
}

function (_Function.funcTest) {
_Function.funcTest:
    _T140 := 1
    _T8 := _T140
    return _T8
}

function (_Function.errorRetType) {
_Function.errorRetType:
    _T141 := 1
    return _T141
}

function (_Statement.stmt2) {
_Statement.stmt2:
_L23:
    _T143 := 0
    _T144 := _T142 > _T143
    if (_T144 == 0) jmp _L24
    _T146 := 1
    _T147 := _T142 - _T146
    _T142 := _T147
    _T148 := 1
    _T149 := _T142 - _T148
    _T145 := _T149
    jmp _L23
_L24:
_L25:
    _T150 := 0
    _T151 := _T142 < _T150
    if (_T151 == 0) jmp _L26
    _T153 := 1
    _T154 := _T152 - _T153
    _T152 := _T154
    _T155 := 1
    _T156 := _T142 + _T155
    _T142 := _T156
    jmp _L25
_L26:
    _T157 := 0
    _T142 := _T157
    jmp _L27
_L28:
    _T158 := 1
    _T159 := _T142 + _T158
    _T142 := _T159
_L27:
    _T160 := 10
    _T161 := _T142 < _T160
    if (_T161 == 0) jmp _L29
    parm _T142
    call _PrintInt
    jmp _L28
_L29:
}

function (_Variable.varTest) {
_Variable.varTest:
    _T162 := *(_T12 + 4)
    _T163 := 5
    _T164 := 4
    _T165 := _T164 * _T163
    _T166 := _T164 + _T165
    parm _T166
    _T167 :=  call malloc
    *(_T167 + 0) := _T163
    _T168 := 0
    _T167 := _T167 + _T166
_L30:
    _T166 := _T166 - _T164
    if (_T166 == 0) jmp _L31
    _T167 := _T167 - _T164
    *(_T167 + 0) := _T168
    jmp _L30
_L31:
    *(_T12 + 4) := _T167
    _T169 := *(_T12 + 4)
    _T170 := 1
    _T171 := 4
    _T172 := _T170 * _T171
    _T173 := _T169 + _T172
    _T174 := *(_T173 + 0)
    _T175 := 1
    _T176 := 4
    _T177 := _T175 * _T176
    _T178 := _T174 + _T177
    _T179 := *(_T178 + 0)
    return _T179
}

function (main) {
main:
    _T181 := 1
    _T180 := _T181
    _T183 :=  call _Mac_New
    _T182 := _T183
    _T184 := 2
    parm _T184
    parm _T182
    _T185 := *(_T182 + 0)
    _T186 := *(_T185 + 8)
    _T187 :=  call _T186
    parm _T182
    _T188 := *(_T182 + 0)
    _T189 := *(_T188 + 12)
    call _T189
    _T191 :=  call _Function_New
    _T190 := _T191
    _T192 := 3
    _T193 := _T180 * _T192
    parm _T193
    parm _T190
    _T194 := *(_T190 + 0)
    _T195 := *(_T194 + 12)
    _T196 :=  call _T195
}

