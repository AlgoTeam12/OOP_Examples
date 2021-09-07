#pragma once
//it will be more evil if we uncomment next line, no warning in general in that case
// #undef NULL
#define NULL (int*)0x777
// it will be worked only for int*, but still can do some damage to us, as the conversion to pointer type work for literal 0
// so no 0x777 for pointers in general 