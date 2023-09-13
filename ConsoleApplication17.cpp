// ConsoleApplication17.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable  : 4996)

#include <iostream>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

int main()
{
	void* shared_ptr = new char[100]; // 这里是位于共享内存的地址
	size_t shared_size = 100;
	size_t used_size;

	int a{ 1 }, b{ 2 }, c{ 3 }, d{ 4 }, aa, bb, cc, dd;
	{ //位于进程A
		yas::mem_ostream os{shared_ptr, shared_size};
		yas::binary_oarchive<yas::mem_ostream> oa{os};
		oa& YAS_OBJECT("i", a, b, c, d); // 数据序列化存放于共享内存中,从而减少一次拷贝操作
		used_size = os.get_shared_buffer().size;
	}
	yas::intrusive_buffer buf((char*)shared_ptr, used_size);
	{ //位于进程B
		yas::mem_istream is(buf);
		yas::binary_iarchive<yas::mem_istream> ia(is);
		ia& YAS_OBJECT("i", aa, bb, cc, dd);
		std::cout << aa << bb << cc << dd << std::endl;
	}

	// 补充性能比较，a.序列化 + 拷贝到目标位置，b.基于目标位置的序列化


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
