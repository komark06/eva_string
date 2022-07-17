# eva_string
## Introduction
My own version of [sds](https://github.com/antirez/sds) .
A C string library that use heap to allocate memory for string.
## Feature of eva_string 
### Binary safe
We store the length of string and allocated size of string in header and add extra null term at the end of string.

### Compatible with C standard string function
You can still use C standard string function. Example down below.
```c
evastr str = evanew("Hello");
printf("%zu",strlen(str));

output > 5
```
### Access every character intuitively
You can treat `eva_string` as C-style string , so access every character is allowed.
```c
evastr str = evanew("Hello");
printf("%c %c",str[0],str[4]);

output > H o
```
### Easy to use
You don't need to worry about memory management of string , `eva_string` will do the work for you. The only thing you have to do, is checking the return value of function.
```c
evastr str = evanew("Hello");
if (!str){
    /* handle error */
}
str = evacpy(str,"Hello world");// eva_string will allocate more memory for bigger string
if (!str){
    /* handle error */
}
```
## How to use
### Declare eva_string
In `eva_string.h` , it declares `evastr` as `char*`. It is better to declare `eva_string` by using `evastr` rather than `char*` . Because it will remind you that you are dealing with `eva_sting` , not a C-style string.

### Create string
There are several ways to create `eva_string` .
```c
evastr evaempty(void);
evastr evanew(const char *src);
evastr evannew(const char *src , size_t len);
evastr evadup(const evastr src);
evastr evaLL(long long value);
```
The `evaempty` function creates empty `eva_string` :
```c
evastr test = evaempty();
printf("%zu\n",evalen(test));

output > 0
```
The `evanew` function creates `eva_string` from null-terminated string.  
The `evannew` function is similar to `evanew`. But it doesn't expect a null-terminated string, so it has additional length parameter. If `src` is `NULL` , content of string will set to `"\0"` .
The `evadup` function creates `eva_string` from another `eva_string` .
```c
evastr test = evanew("Hello");
evastr str = evadup(test);
printf("%s\n",str);

output > Hello
```
The `evaLL` function creates `eva_string` from integer.
```c
evastr test = evaLL(100);
printf("%s\n",test);

output > 100
```
### Obtain length and space of string
```c
uint32_t evalen(evastr nerv);
```
The `evalen` function return true length of `eva_string` . Having a null term in the middle of string, doesn't change the length of string.
```c
evastr test = evannew("1\02",3);
printf("%u %zu",evalen(test),strlen(test));

output > 3 2
```
### Copy string
```c
evastr evacpy(evastr restrict dst , const char *restrict src);
evastr evancpy(evastr restrict dst , const char *restrict src , size_t len);
```
The `evacpy` function copies `src` to `dst`. `src` must be null-terminated string.  
The `evancpy` function is similar to `evacpy` . But it doesn't expect a null-terminated string, so it has additional length parameter.   
Both functions will make sure that there is a null term at the end of string.
```c
str = evancpy(str,"eva");
str = evancpy(str,"EVA",3);
```
Unlike the `strcpy` function of C standard function, `evacpy` needs to receive `eva_string` back. Because `evacpy` may change the value of `eva_string`, like allocating a larger memory for `eva_string`. For secure coding, it is necessary to check return value.
### Concatenate string
```c
evastr evacat(evastr dst , const char *src);
evastr evancat(evastr dst , const char *src , size_t len);
evastr evacateva(evastr dst , const evastr src);
evastr evacatprintf(evastr dst , const char *format , ...);
```
The `evacat` function concatenates `src` to `dst` . `src` must be null-terminated string.  
The `evancat` function is similar to `evacat`. But it doesn't expect a null-terminated string, so it has additional length parameter.  
```c
evastr test = evaempty();
test = evacat("EVA");
printf("%s",test);

output > EVA
```
The `evacateva` function concatenates from `eva_string`. So it doesn't need length to operate.
```c
evastr str1 = evanew("EVA");
evastr str2 = evanew("STR");
str1 = evacateva(str1,str2);
printf("%s",str1);

output > EVASTR
```
`evacatprintf` is a special function for concatenating. It concatenates formatted string. Format specifiers are from `printf` family.
```c
evastr test = evacatprintf(evaempty(),"%d + %d = %d",10,20,30);
printf("%s",test);

output > 10 + 20 = 30
```
### Resize string
```c
evastr evaresize(evastr dst);
```
The `evaresize` function resizes `eva_string` to minimum size .
### Destroy string
```c
void evafree(evastr nerv);
```
Destroy a `eva_string` , just call `evafree`. You don't need to check `NULL` before calling `evafree`.
