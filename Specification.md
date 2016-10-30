# Dragon Language Specification

## Declaration

```java
// defination section(with/without initialization)
...

// initialization section
...

// other sections
...
```

## Function

```java
// function defination
int sayHelloFunc = (void) => {
    Print("Hello World!\n");
    return 0;
};

// anonymous fucntions invoking, then assign return value to a variable
int sayHelloVar = int (void) => {
    Print("Hello World!\n");
    return 0;
}();
```
