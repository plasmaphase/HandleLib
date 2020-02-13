#ifndef ASSERT_H_
#define ASSERT_H_

// If the condition is false, attempts to extern an array with negative length causing error
#define M_CompileTimeAssert(cond) extern char compile_time_assert[(cond)?1:-1]

//****************************************************************************************************************************

#endif // ASSERT_H_
