#include "pch.h"
#include "CppUnitTest.h"
#include "../[SibFU 6] - Theory_of_Programming - Procedural/Header.h"
#include "../[SibFU 6] - Theory_of_Programming - Procedural/Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		std::string PATH = "..\\[SibFU 6] - Theory_of_Programming - Procedural\\Test\\";
		TEST_METHOD(inTextTest)
		{
			ifstream ifst(PATH + "in\\inText.txt");
			Text* T = inText(ifst);
			Assert::AreEqual((int)T->K, (int)APHORISM);
		}
		TEST_METHOD(inAphorismTest)
		{
			ifstream ifst(PATH + "in\\inAphorism.txt");
			Aphorism* A = inAphorism(ifst);
			Assert::AreEqual(A->text, (string)"Text");
			Assert::AreEqual(A->author, (string)"Author");
			Assert::AreEqual(A->mark, 10);
		}
		TEST_METHOD(outAphorismTest)
		{
			Aphorism* A = new Aphorism();
			A->K = APHORISM;
			A->text = "Out.Text";
			A->author = "Pushkin";
			A->mark = 4;
			ofstream ofst(PATH + "out\\outAphorismActual.txt");
			outAphorism(A, ofst);
			ifstream ifstActual(PATH + "out\\outAphorismActual.txt");
			ifstream ifstExpected(PATH + "out\\outAphorismExpected.txt");
			string Expected;
			getline(ifstExpected, Expected, '\0');
			string Actual;
			getline(ifstActual, Actual, '\0');
			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(inSayingTest)
		{
			ifstream ifst(PATH + "in\\inSaying.txt");
			Saying* S = inSaying(ifst);
			Assert::AreEqual(S->text, (string)"Text");
			Assert::AreEqual(S->country, (string)"Country");
			Assert::AreEqual(S->mark, 10);
		}
		TEST_METHOD(outSayingTest)
		{
			Saying* S = new Saying();
			S->K = SAYING;
			S->text = "Saying-Text.";
			S->country = "Moldova";
			S->mark = 5;
			ofstream ofst(PATH + "out\\outSayingActual.txt");
			outSaying(S, ofst);
			ifstream ifstActual(PATH + "out\\outSayingActual.txt");
			ifstream ifstExpected(PATH + "out\\outSayingExpected.txt");
			string Expected;
			getline(ifstExpected, Expected, '\0');
			string Actual;
			getline(ifstActual, Actual, '\0');
			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(inRiddleTest)
		{
			ifstream ifst(PATH + "in\\inRiddle.txt");
			Riddle* R = inRiddle(ifst);
			Assert::AreEqual(R->text, (string)"Any-Riddle-Here?");
			Assert::AreEqual(R->answer, (string)"Answer");
			Assert::AreEqual(R->mark, 2);
		}
		TEST_METHOD(outRiddleTest)
		{
			Riddle* R = new Riddle();
			R->K = RIDDLE;
			R->text = "Qute, but not qt";
			R->answer = "Love";
			R->mark = 9;
			ofstream ofst(PATH + "out\\outRiddleActual.txt");
			outRiddle(R, ofst);
			ifstream ifstActual(PATH + "out\\outRiddleActual.txt");
			ifstream ifstExpected(PATH + "out\\outRiddleExpected.txt");
			string Expected;
			getline(ifstExpected, Expected, '\0');
			string Actual;
			getline(ifstActual, Actual, '\0');
			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(functionTest)
		{
			ifstream ifst(PATH + "function\\punctuation.txt");
			Riddle* R = inRiddle(ifst);
			Assert::AreEqual(textCounter((Text*)R), 4);
		}
		TEST_METHOD(compatatorTest)
		{
			int K;
			ifstream ifst(PATH + "function\\comparator.txt");
			Container* first = new Container;
			Container* second = new Container;
			ifst >> K;
			first->current = (Text*)inRiddle(ifst);
			first->current->K = (Key)K;
			ifst >> K;
			second->current = (Text*)inRiddle(ifst);
			second->current->K = (Key)K;
			bool Actual = compare(first->current, second->current);
			Assert::AreEqual(Actual, true);
		}
		TEST_METHOD(sortTest)
		{
			ifstream ifst(PATH + "function\\sort.txt");
			Container* Head = new Container();
			Container* Tail = new Container();
			initContainer(Head, Tail);
			inContainer(Head, Tail, ifst);
			ofstream ofst(PATH + "function\\sortActual.txt");
			sort(Head);
			outContainer(Head, ofst);
			ifstream ifstExpected(PATH + "function\\sortExpected.txt");
			ifstream ifstActual(PATH + "function\\sortActual.txt");
			string Expected;
			getline(ifstExpected, Expected, '\0');
			string Actual;
			getline(ifstActual, Actual, '\0');
			Assert::AreEqual(Expected, Actual);
		}
	};
}
