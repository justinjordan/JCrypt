#include "../src/jcrypt.h"

#include <cstdio>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

SCENARIO("create hash using password, then authenticate", "[hashauth]") {

    GIVEN("a password string") {

        std::string password, salt, hash;
        password = "badpassword";
        salt = jcrypt::createSalt(1);

        REQUIRE( !salt.empty() );

        WHEN("hash is generated") {

            hash = jcrypt::createHash(password, salt);

            REQUIRE ( !hash.empty() );

            THEN("authenticate password using hash") {

                REQUIRE( jcrypt::authenticate(password, hash) );

            }
        }
    }
}
