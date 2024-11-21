# File Name Conventions  
To automate the unit testing as much as possible, file name conventions have been adopted. A file name prependend with `ptp_` is a **Positive Test Path** unit test. A file name prependend with `ntp_` is a **Negative Test Path** unit test.  

Unit test file names should include input type of the data for the constructor being tested, examples:  
 - `ptp_array` for std::array input  
 - `ntp_array` for std::array input  
 - `ptp_vector` for std::vector input
 - `ntp_vector` for std::vector input
 - `ptp_initList` for initialization lists  
 - `ntp_initList` for initialization lists  
 
 What is being tested, as an example a negative path test using an array to test duplicate IDs should be named `ntp_arrayDupID`. A positive path test using a vector to test the both `lookupID()` and `lookupName()` can be named `ptp_vectorLookup`.   
 
 # Exceptions  
 All test files should handle exceptions, while CTest is capable of handling the exceptions, not all exceptions are failures, especially in the negative unit test cases.  
 
 
