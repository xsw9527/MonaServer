
#include "UtilTest.h"
#include "Mona/Util.h"
#include <cstring>

using namespace Mona;

using namespace std;

Buffer<UInt8> Result;

void TestEncode(const char* data,UInt32 size, const char* result) {
	Util::ToBase64((UInt8*)data, size, Result);
	EXPECT_TRUE(strlen(result) == Result.size() && memcmp(Result.data(), result, Result.size()) == 0);
}

bool TestDecode(const char* data, const char* result, UInt32 size) {
	bool success = Util::FromBase64((UInt8*)data, strlen(data), Result);
	EXPECT_TRUE(size == Result.size() && memcmp(Result.data(), result, Result.size()) == 0);
	return success;
}

ADD_TEST(UtilTest, Base64) {
	TestEncode("\00\01\02\03\04\05", 6,"AAECAwQF");
	TestEncode("\00\01\02\03",4, "AAECAw==");
	TestEncode("ABCDEF", 6,"QUJDREVG");

	EXPECT_TRUE(TestDecode("AAECAwQF", "\00\01\02\03\04\05", 6));
	EXPECT_TRUE(TestDecode("AAECAw==", "\00\01\02\03", 4));
	EXPECT_TRUE(TestDecode("QUJDREVG", "ABCDEF", 6));
	EXPECT_TRUE(TestDecode("QUJ\r\nDRE\r\nVG", "ABCDEF", 6));
	EXPECT_TRUE(!TestDecode("QUJD#REVG", "ABCDEF", 6));

	string message("The quick brown fox jumped over the lazy dog.");
	Util::ToBase64((const UInt8*)message.c_str(), message.size(), Result);
	Buffer<UInt8> buffer;
	EXPECT_TRUE(Util::FromBase64(Result.data(), Result.size(), buffer));
	EXPECT_TRUE(memcmp(buffer.data(), message.c_str(), message.size()) == 0);

	UInt8 data[255];
	for (UInt8 i = 0; i < 255; ++i)
		data[i] = i;
	Util::ToBase64(data, sizeof(data), Result);
	EXPECT_TRUE(Util::FromBase64(Result.data(), Result.size(), buffer));
	EXPECT_TRUE(memcmp(buffer.data(), data, sizeof(data)) == 0);
}


ADD_TEST(UtilTest, FormatHex) {
	string result;
	Util::FormatHexCpp((const UInt8*)"\00\01\02\03\04\05", 6, result);
	EXPECT_TRUE(result == "\\x00\\x01\\x02\\x03\\x04\\x05")

	Util::FormatHex((const UInt8*)"\00\01\02\03\04\05", 6, result);
	EXPECT_TRUE(result == "000102030405")

	UInt32 size = result.size();
	Util::UnformatHex((UInt8*)result.c_str(), size);
	EXPECT_TRUE(memcmp(result.c_str(), "\00\01\02\03\04\05", size) == 0)
}
