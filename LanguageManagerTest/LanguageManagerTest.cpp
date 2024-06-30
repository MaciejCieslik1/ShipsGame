#include "CppUnitTest.h"
#include "../Ships/LanguageManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LanguageManagerTest
{
	TEST_CLASS(LanguageManagerTest)
	{
	public:

		// Helper func to create file for testing
		void createTestFile(const std::string& filename, const std::string& content) {
			std::ofstream file(filename);
			file << content;
			file.close();
		}

		TEST_METHOD(Constructor)
		{
			LanguageManager manager("testfile.txt");
			Assert::IsTrue(true);
		}

		TEST_METHOD(LoadAndGetCommunicates)
		{
			const std::string testFileName = "testfile.txt";
			const std::string fileContent = "greeting=Hello\nfarewell=Goodbye\n";
			createTestFile(testFileName, fileContent);

			LanguageManager manager(testFileName);
			manager.loadCommunicates();

			Assert::AreEqual(std::string("Hello"), manager.getCommunicate("greeting"));
			Assert::AreEqual(std::string("Goodbye"), manager.getCommunicate("farewell"));
			
			auto func = [&manager]() { manager.getCommunicate("unknown"); };
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(LoadCommunicatesFileNotFound)
		{
			LanguageManager manager("nonexistentfile.txt");
			auto func = [&manager]() { manager.loadCommunicates(); };
			Assert::ExpectException<std::runtime_error>(func);
		}
	};
}
