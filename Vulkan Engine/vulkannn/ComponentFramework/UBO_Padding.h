#pragma once

/*** A Uniform Buffer Object declares a block of GPU memory that can be used 
to store any kind of data you wish. That data can then be used in any number of 
shaders that needs it. 

The twist is that between the CPU and the GPU the sizes of each chunk of data
must have the size and layout on both devices. To accomplish this, a set of rules
that standardize memory sizes and layout was astablished known as std140. The 
full set of rules can be found here: 
https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_uniform_buffer_object.txt

Below, is a set of const sizes for most the data used in Graphics programming based
on std140. Notice that even a bool if 4 bytes long and both Vec3 and Vec4 are 16 bytes. 
-Scott
***/
 struct UBO_PADDING {
 private:
	const static size_t BASE_ALIGNMENT = 4; /// Four Byte Chunks
 public:
	 /// Based on the std140 rules
	const static size_t INT = BASE_ALIGNMENT;
	const static size_t FLOAT = BASE_ALIGNMENT;
	const static size_t BOOL = BASE_ALIGNMENT;
	const static size_t DOUBLE = BASE_ALIGNMENT;
	const static size_t VEC2 = 2 * BASE_ALIGNMENT;
	const static size_t VEC3 = 4 * BASE_ALIGNMENT;
	const static size_t VEC4 = 4 * BASE_ALIGNMENT;
	const static size_t MAT4 = 4 * VEC4;
	const static size_t MAT3 = 4 * VEC4;
};

