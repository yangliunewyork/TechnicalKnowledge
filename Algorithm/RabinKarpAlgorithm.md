## Reference

http://www.geeksforgeeks.org/searching-for-patterns-set-3-rabin-karp-algorithm/

## What is Rabin-Karp ?
In computer science, the Rabin–Karp algorithm or Karp–Rabin algorithm is a string searching algorithm created by Richard M. Karp and Michael O. Rabin (1987) that uses hashing to find any one of a set of pattern strings in a text. For text of length n and p patterns of combined length m, its average and best case running time is O(n+m) in space O(p), but its worst-case time is O(nm).

A practical application of the algorithm is detecting plagiarism. Given source material, the algorithm can rapidly search through a paper for instances of sentences from the source material, ignoring details such as case and punctuation. Because of the abundance of the sought strings, single-string searching algorithms are impractical.

## Hash function used
The key to the Rabin–Karp algorithm's performance is the efficient computation of hash values of the successive substrings of the text. The Rabin fingerprint is a popular and effective rolling hash function. The Rabin fingerprint treats every substring as a number in some base, the base being usually a large prime. For example, if the substring is "hi" and the base is 101, the hash value would be 104 × 1011 + 105 × 1010 = 10609 (ASCII of 'h' is 104 and of 'i' is 105).

Technically, this algorithm is only similar to the true number in a non-decimal system representation, since for example we could have the "base" less than one of the "digits". See hash function for a much more detailed discussion. The essential benefit achieved by using a rolling hash such as the Rabin fingerprint is that it is possible to compute the hash value of the next substring from the previous one by doing only a constant number of operations, independent of the substrings' lengths.

For example, if we have text "abracadabra" and we are searching for a pattern of length 3, the hash of the first substring, "abr", using 101 as base is:

```
// ASCII a = 97, b = 98, r = 114. 
hash("abr") = (97 × 1012) + (98 × 1011) + (114 × 1010) = 999,509 
```

We can then compute the hash of the next substring, "bra", from the hash of "abr" by subtracting the number added for the first 'a' of "abr", i.e. 97 × 1012, multiplying by the base and adding for the last a of "bra", i.e. 97 × 1010. Like so:

```
//             base   old hash    old 'a'         new 'a'
hash("bra") = [1011 × (999,509 - (97 × 1012))] + (97 × 1010) = 1,011,309
```

## Code (has some bug, need to check again)

~~~~
#include <iostream>

const int NUM_OF_CHARACTERS(256);

std::vector<std::size_t> RabinKarpSearch(const std::string & pattern,
                                         const std::string & text,
                                         const std::size_t prime) {
  std::vector<std::size_t> reval;
  
  const std::size_t pattern_size(pattern.size()), text_size(text.size());

  if (pattern_size > text_size) return reval;
  
  std::size_t pattern_index(0),text_index(0);
  
  int pattern_hash(0), text_hash(0);
  int h(1);
  
  // The value of h would be "pow(d, M-1)%q"
  for (std::size_t i = 0; i < pattern_size; ++i) {
    h = (h * NUM_OF_CHARACTERS) % prime;
  }
  
  // Calculate the hash value of pattern and first
  // window of text
  for (std::size_t i = 0; i < pattern_size; ++ i) {
    pattern_hash = (NUM_OF_CHARACTERS * pattern_hash + pattern[i]) % prime;
    text_hash = (NUM_OF_CHARACTERS * text_hash + text[i]) % prime;
  }

  
  for (text_index = 0; text_index <= text_size - pattern_size; ++ text_index) {

    // Check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters on by one
    if (pattern_hash == text_hash) {

      for (pattern_index = 0; pattern_index < pattern_size; ++ pattern_index) {
        if (pattern[pattern_index] != text[text_index + pattern_index]) {
          break;
        }
      }
      if (pattern_index == pattern_size) reval.push_back(text_index);
    }
 
    // Calculate hash value for next window of text: Remove
    // leading digit, add trailing digit
    if (text_index < text_size - pattern_size) {
      text_hash = ( NUM_OF_CHARACTERS * (text_hash - text[text_index] * h)
                    + text[text_index + pattern_size]) % prime;
      if (text_hash < 0) {
        text_hash += prime;
      }
    }
  }

  return reval;
}
int main() {
  std::vector<std::size_t> reval = RabinKarpSearch("GEEK","GEEKS FOR GEEKS",101);
  for (std::size_t val : reval) {
    std::cout << val << std::endl;
  }
  return 0;
}
~~~~
