
#include "../include/Catch2/catch.h"
#include "../include/rsa.h"

SCENARIO("Testing Lehman Peralta test for prime numbers")
{
  GIVEN("numbers divisible y 2,3,5,7 or 11")
  {
    WHEN("Apllied test")
    {
      THEN("Returns false in all cases")
      {
        // CHECK(le_pe_test(4) == false);
        // CHECK(le_pe_test(8) == false);
        // CHECK(le_pe_test(6) == false);
        // CHECK(le_pe_test(9) == false);
        // CHECK(le_pe_test(10) == false);
        // CHECK(le_pe_test(55) == false);
        // CHECK(le_pe_test(42) == false);
        // CHECK(le_pe_test(77) == false);
        // CHECK(le_pe_test(121) == false);
        // CHECK(le_pe_test(33) == false);
      }
    }
  }
  GIVEN("Prime numbers larger than 2,3,5,7 or 11")
  {
    WHEN("applied test with one attempt and number 13")
    {
      THEN("returns mostly false")
      {
        //CHECK(le_pe_test(13) == false);
      }
    }
    AND_WHEN("applied test with one attempt and number 39")
    {
      THEN("returns mostly true")
      {
        // CHECK(le_pe_test(7919) == true);
      }
    }
  }
}

SCENARIO("Testing message ecnoding to upper")
{
  GIVEN("Capitalized string")
  {
    std::string str = "HELLO WORLD";
    WHEN("transforming string to upper")
    {
      to_upper(str);
      THEN("String isnt changed")
      {
        CHECK(str == "HELLO WORLD");
      }
    }
  }
  AND_GIVEN("Non capitalized string")
  {
    std::string str = "Hello world";
    WHEN("transforming string to upper")
    {
      to_upper(str);
      THEN("String isnt changed")
      {
        CHECK(str == "HELLO WORLD");
      }
    }
  }
}

SCENARIO("Block encoding")
{
  GIVEN("A string message and n-value")
  {
    std::string msg = "HELLO WORLD";
    long n = 2947;
    WHEN("computing the block size")
    {
      long sz = block_sz(n);
      THEN("String isnt changed")
      {
        CHECK(sz == 2);
      }
    }
    AND_WHEN("Computing block number value for ABCD")
    {
      long encoded_str = encode("ABCD EF", 4)[0];
      THEN("encoded single block value is 731")
      {
        CHECK(encoded_str == 731);
      }
    }
    AND_WHEN("Trying MANDA DINEROS")
    {
      THEN("Returns expected values")
      {
        CHECK(encode("MANDA DINEROS", block_sz(2947))[0] == 312);
        CHECK(encode("MANDA DINEROS", block_sz(2947))[1] == 341);
        CHECK(encode("MANDA DINEROS", block_sz(2947))[2] == 3);
        CHECK(encode("MANDA DINEROS", block_sz(2947))[3] == 221);
        CHECK(encode("MANDA DINEROS", block_sz(2947))[4] == 121);
        CHECK(encode("MANDA DINEROS", block_sz(2947))[5] == 382);
      }
    }
    AND_WHEN("Trying AMIGO MIO")
    {
      THEN("Returns expected values")
      {
        CHECK(encode("AMIGO MIO", block_sz(2347 * 347))[0] == 8326);
        CHECK(encode("AMIGO MIO", block_sz(2347 * 347))[1] == 254398);
      }
    }
  }
}

SCENARIO("Testing extended euclidean (GCD extended) for the e parameter")
{
  GIVEN("d=1619 and phi=2520")
  {
    WHEN("Applied euclidean extended")
    {
      THEN("e=179")
      {
        CHECK(mod_mult_inv(1619, 2520) == 179);
      }
      AND_THEN("Reversed proccess works")
      {
        CHECK(mod_mult_inv(179, 2520) == 1619);
      }
    }
  }
}

SCENARIO("High end ciphering test case")
{
  GIVEN("msg=MANDA DINEROS, p=421, q=7 and d=1619")
  {
    long p = 421, q = 7, d = 1619;
    long n = p * q, phi = (p - 1) * (q - 1);
    std::string msg = "manda dineros";
    to_upper(msg);
    WHEN("Checking p and q prime numbers")
    {
      THEN("checker may return true")
      {
        CHECK(is_prime(421));
        CHECK(is_prime(7));
      }
    }
    AND_WHEN("Checking d with phi(n) prime number")
    {
      THEN("checker may return true")
      {
        CHECK(is_prime(mod_mult_inv(d, phi)));
      }

      AND_THEN("Computing e")
      {
        CHECK(mod_mult_inv(d, phi) == 179);
      }
    }
    AND_WHEN("Encoding message")
    {
      THEN("Expected blocks are returned")
      {

        CHECK(encode(msg, block_sz(n))[0] == 312);
        CHECK(encode(msg, block_sz(n))[1] == 341);
        CHECK(encode(msg, block_sz(n))[2] == 3);
        CHECK(encode(msg, block_sz(n))[3] == 221);
        CHECK(encode(msg, block_sz(n))[4] == 121);
        CHECK(encode(msg, block_sz(n))[5] == 382);
      }
    }
    AND_WHEN("Ciphering message")
    {
      THEN("cipher block array is returned")
      {
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[0] == 2704);
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[1] == 2173);
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[2] == 404);
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[3] == 2340);
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[4] == 1789);
        CHECK(cipher(encode(msg, block_sz(n)), mod_mult_inv(d, phi), n)[5] == 2333);
      }
    }
  }
}