#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_11.5/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestAddProduct)
		{
			vector<Product> products;

			// Add a product
			Product testProduct;
			testProduct.type = "drink";
			testProduct.calorie = 100;
			testProduct.price = 2.5;
			testProduct.drink.strength = 5.0;
			products.push_back(testProduct);

			// Check if product was added correctly
			Assert::AreEqual(products.size(), size_t(1));
			Assert::AreEqual(products[0].type, string("drink"));
			Assert::AreEqual(products[0].calorie, 100.0);
			Assert::AreEqual(products[0].price, 2.5);
			Assert::AreEqual(products[0].drink.strength, 5.0);
		}

		TEST_METHOD(TestReplaceProduct)
		{
			vector<Product> products;

			// Add a product
			Product testProduct;
			testProduct.type = "chocolate";
			testProduct.calorie = 200;
			testProduct.price = 3.0;
			testProduct.chocolate.weight = 50;
			testProduct.chocolate.filling = "hazelnut";
			products.push_back(testProduct);

			// Replace the product
			Product newData;
			newData.type = "drink";
			newData.calorie = 150;
			newData.price = 2.0;
			newData.drink.strength = 7.5;
			int index = 0;
			products[index] = newData;

			// Check if product was replaced correctly
			Assert::AreEqual(products.size(), size_t(1));
			Assert::AreEqual(products[0].type, string("drink"));
			Assert::AreEqual(products[0].calorie, 150.0);
			Assert::AreEqual(products[0].price, 2.0);
			Assert::AreEqual(products[0].drink.strength, 7.5);
		}

		TEST_METHOD(TestDeleteProduct)
		{
			vector<Product> products;

			// Add a product
			Product testProduct;
			testProduct.type = "drink";
			testProduct.calorie = 100;
			testProduct.price = 2.5;
			testProduct.drink.strength = 5.0;
			products.push_back(testProduct);

			// Add another product
			Product testProduct2;
			testProduct2.type = "chocolate";
			testProduct2.calorie = 200;
			testProduct2.price = 3.0;
			testProduct2.chocolate.weight = 50;
			testProduct2.chocolate.filling = "hazelnut";
			products.push_back(testProduct2);

			// Delete products of type "drink"
			deleteFromFile("products.bin", "drink");
		}
	};
}
