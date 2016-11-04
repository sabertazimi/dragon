class Statement {
    void stmt1 = (void) => {
        int x = 1;

        // syntax error: unmatched '(' or ')'
        if x > 0) {
            return;
        }

        // syntax error: unmatched '(' or ')'
        if (x > 0 {
            return;
        }

        // syntax error: unmatched '{' or '}'
        if (x > 0)
            return;
        }
    };

    void stmt2 = (void) => {
        int x = 10;

        // syntax error: unmatched '(' or ')'
        while x > 0) {
            x = x - 1;
        }

        // syntax error: unmatched '(' or ')'
        while (x > 0 {
            x = x - 1;
        }

        // syntax error: unmatched '{' or '}'
        while (x > 0)
            x = x - 1;
        }
    };

    void stmt3 = (void) => {
        int x;

        // syntax error: unmatched '(' or ')'
        for x = 0; x < 10; x = x + 1) {
            Print(x);
        }

        // syntax error: expected keyword 'void' or assign expression
        for (; x < 10; x = x + 1) {
            Print(x);
        }

        // syntax error: expected ';' as separator between initializer and boolean expression
        for (x = 0 x < 10; x = x + 1) {
            Print(x);
        }

        // syntax error: expected ';' as separator between boolean expression and assignment
        for (x = 0; x < 10 x = x + 1) {
            Print(x);
        }

        // syntax error: unmatched '(' or ')'
        for (x = 0; x < 10; x = x + 1 {
            Print(x);
        }

        // syntax error: unmatched '{' or '}'
        for (x = 0; x < 10; x = x + 1)
            Print(x);
        }
    };

    void stmt4 = (void) => {
        // syntax error: unkown return value
        return int (int foo) => {
            return foo * 2;
        };
    };

    void stmt5 = (void) => {
        // syntax error: unmatched '(' or ')'
        Print "233\n");

        // syntax error: unmatched '(' or ')'
        Print("233\n";

        // syntax error: expected ';'
        Print("233\n")
    }
}
