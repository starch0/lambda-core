type True = <T>(x: T) => <V>(y: V) => T;
type False = <T>(x: T) => <V>(y: V) => V;

const _true: True = x => y => x;
const _false: False = x => y => y;

type Not<A extends True | False> = A extends True ? False : True;
type And<A1 extends True | False, A2 extends True | False> =
    A1 extends True ? A2 : False;

type Or<A1 extends True | False, A2 extends True | False> =
    A1 extends True ? True : A2;

type ChurchNumeral = <T>(f: (x: T) => T) => (x: T) => T;

const _zero: ChurchNumeral = f => x => x;

const _successor = <T>(n: ChurchNumeral): ChurchNumeral =>
    f => x => f(n(f)(x));

// One
const _one: ChurchNumeral = _successor(_zero);

// Two
const _two: ChurchNumeral = _successor(_one);

// Type tests
type TestTrue = True extends True ? true : false;
type TestFalse = False extends False ? true : false;

type TestNotTrue = Not<True> extends False ? true : false;
type TestNotFalse = Not<False> extends True ? true : false;

type TestAndTrueTrue = And<True, True> extends True ? true : false;
type TestAndTrueFalse = And<True, False> extends False ? true : false;
type TestAndFalseTrue = And<False, True> extends False ? true : false;
type TestAndFalseFalse = And<False, False> extends False ? true : false;

type TestOrTrueTrue = Or<True, True> extends True ? true : false;
type TestOrTrueFalse = Or<True, False> extends True ? true : false;
type TestOrFalseTrue = Or<False, True> extends True ? true : false;
type TestOrFalseFalse = Or<False, False> extends False ? true : false;

// Helper function 
const applyNumeral = <T>(
    numeral: ChurchNumeral,
    f: (x: T) => T,
    initial: T
): T => numeral(f)(initial);

// Increment helper
const increment = (n: ChurchNumeral): ChurchNumeral => _successor(n);

// Pair type for predecessor implementation
type Pair<A, B> = [A, B];

// Predecessor implementation
const predecessor = (n: ChurchNumeral): ChurchNumeral => {
    const pair = n((p: Pair<ChurchNumeral, ChurchNumeral>) => {
        const [_, prev] = p;
        return [prev, _successor(prev)] as Pair<ChurchNumeral, ChurchNumeral>;
    })([_zero, _zero] as Pair<ChurchNumeral, ChurchNumeral>);
    
    return pair[0];
};

// Tests
const testNumerals = () => {
    // Test basic numerals
    console.log("Zero:", applyNumeral(_zero, (x: number) => x + 1, 0));  // Should be 0
    console.log("One:", applyNumeral(_one, (x: number) => x + 1, 0));   // Should be 1
    console.log("Two:", applyNumeral(_two, (x: number) => x + 1, 0));   // Should be 2

    // Test predecessor
    console.log("Pred Zero:", applyNumeral(predecessor(_zero), (x: number) => x + 1, 0));  // Should be 0
    console.log("Pred One:", applyNumeral(predecessor(_one), (x: number) => x + 1, 0));    // Should be 0
    console.log("Pred Two:", applyNumeral(predecessor(_two), (x: number) => x + 1, 0));    // Should be 1
};

testNumerals();