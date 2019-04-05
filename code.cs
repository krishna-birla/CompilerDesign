using System;
using Util;

public class MainClass
{
	private volatile char[] c = new char[5];
	int x = 12;
	public static void func(string argv)
	{
		switch(x = 6 + 4 * 2)
		{
			case 12:{
				break;
			}
			default:{
				break;
			}
		}
	}
}

namespace Example
{
	public class BaseClass
	{
		protected int a = 6;
		public float b = 7;
		int save(int x, char y)
		{
			a = b + 3;
		}

		static void test(string str, double p)
		{
			//
		}
	}

	class DerivedClass : BaseClss
	{
		private static int[] a = new char[7];
	}

	internal class Empty
	{
		const int[] vec = new int[5];
		static void Main3(string[] args)
		{
			vec[0] = vec[1] + vec[2];
		}
	}

	class HelloWorldClass
	{
		const int[] vec = new int[5];
		static void Main2(string[] args)
		{
			vec[0] = vec[1] + vec[2];
		}
	}
}
