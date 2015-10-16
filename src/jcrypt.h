#ifndef JCRYPT_H
#define JCRYPT_H

#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

class jcrypt {
public:

    static std::string createSalt(int work_factor) {
        work_factor = (work_factor < 1) ? 1 : (work_factor > 99) ? 99 : work_factor;
        std::string output = ((work_factor < 10)?"0":"") + std::to_string(work_factor);
        output += rand_hash(SALT_LENGTH - 2);
        return output;
    }

    static std::string createHash(std::string input, std::string salt) {
        int sum = 0;
        int character, work_factor;
        std::string last_hash = salt.substr(2, salt.length() - 2) + input;
        std::string hash, output;

        work_factor = 10 * salt[0] + salt[1] - 11 * '0'; // thanks algebra!

        for ( int w = 0; w < pow(10, work_factor); w++ ) {
            for ( int j = 0; j < HASH_LENGTH; j++ ) {
                sum += last_hash[ j % last_hash.length() ];
                character = sum % 36;

                hash += convertChar(character);
            }

            last_hash = hash;
            hash = "";
        }

        output = salt + last_hash;

        return output;
    }

    static std::string getSalt(std::string hash) {
        return hash.substr(0, SALT_LENGTH);
    }

    static bool authenticate(std::string str, std::string hash) {

        std::string salt = getSalt(hash);
        std::string newHash = createHash(str, salt);

        return hash == newHash;

    }

private:

    static const int SALT_LENGTH = 18;
    static const int HASH_LENGTH = 64;

    static std::string rand_hash(int length) {

        srand(time(NULL));

        std::string hash;
        int character;

        for ( int i = 0; i < length; i++ ) {
            character = rand() % 36;

            hash += convertChar(character);
        }

        return hash;

    }

    static char convertChar(int character) {

        return ((character < 26) ? character + 97 : character + 22 );

    }

};

#endif
