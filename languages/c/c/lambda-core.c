#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct lambda;

typedef struct lambda (*lambda_t)(struct lambda *, struct lambda);

struct lambda {
	lambda_t f;
	struct lambda *_;
};

struct lambda lambda_call(struct lambda lambda, struct lambda arg)
{
	return lambda.f(lambda._, arg);
}

struct lambda logic__true_(struct lambda *_, struct lambda)
{
	const struct lambda x = _[0];
	return x;
}

struct lambda logic__true(struct lambda *, struct lambda x)
{
	struct lambda *const _ = malloc(sizeof(x));
	_[0] = x;
	return (struct lambda) {logic__true_, _};
}

const struct lambda logic_true = {logic__true};

struct lambda logic__false_(struct lambda *, struct lambda y)
{
	return y;
}

struct lambda logic__false(struct lambda *, struct lambda)
{
	return (struct lambda) {logic__false_};
}

const struct lambda logic_false = {logic__false};

struct lambda logic__not(struct lambda *, struct lambda x)
{
	return lambda_call(lambda_call(x, logic_false), logic_true);
}

const struct lambda logic_not = {logic__not};

struct lambda logic__and_(struct lambda *_, struct lambda y)
{
	const struct lambda x = _[0];
	return lambda_call(lambda_call(x, y), logic_false);
}

struct lambda logic__and(struct lambda *, struct lambda x)
{
	struct lambda *const _ = malloc(sizeof(x));
	_[0] = x;
	return (struct lambda) {logic__and_, _};
}

const struct lambda logic_and = {logic__and};

struct lambda logic__or_(struct lambda *_, struct lambda y)
{
	const struct lambda x = _[0];
	return lambda_call(lambda_call(x, logic_true), y);
}

struct lambda logic__or(struct lambda *, struct lambda x)
{
	struct lambda *const _ = malloc(sizeof(x));
	_[0] = x;
	return (struct lambda) {logic__or_, _};
}

const struct lambda logic_or = {logic__or};

bool logic_test_convert(struct lambda x)
{
	return (uintptr_t) lambda_call(lambda_call(x, (struct lambda) {
		(lambda_t) true
	}), (struct lambda) {
		(lambda_t) false
	}).f;
}

void logic_test_print(struct lambda x)
{
	printf("%hhu\n", logic_test_convert(x));
}

struct lambda church__zero_(struct lambda *, struct lambda x)
{
	return x;
}

struct lambda church__zero(struct lambda *, struct lambda)
{
	return (struct lambda) {church__zero_};
}

const struct lambda church_zero = {church__zero};

struct lambda church__succ__(struct lambda *_, struct lambda x)
{
	const struct lambda n = _[0];
	const struct lambda f = _[1];
	return lambda_call(f, lambda_call(lambda_call(n, f), x));
}

struct lambda church__succ_(struct lambda *_, struct lambda f)
{
	struct lambda *const __ = malloc(2 * sizeof(f));
	__[0] = _[0];
	__[1] = f;
	return (struct lambda) {church__succ__, __};
}

struct lambda church__succ(struct lambda *, struct lambda n)
{
	struct lambda *const _ = malloc(2 * sizeof(n));
	_[0] = n;
	return (struct lambda) {church__succ_, _};
}

const struct lambda church_succ = {church__succ};

struct lambda church_one;

struct lambda church__pred______(struct lambda *, struct lambda a)
{
	return a;
}

struct lambda church__pred_____(struct lambda *_, struct lambda)
{
	const struct lambda x = _[1];
	return x;
}

struct lambda church__pred____(struct lambda *_, struct lambda h)
{
	const struct lambda f = _[0];
	const struct lambda g = _[1];
	return lambda_call(h, lambda_call(g, f));
}

struct lambda church__pred___(struct lambda *_, struct lambda g)
{
	struct lambda *const __ = malloc(2 * sizeof(g));
	__[0] = _[0];
	__[1] = g;
	return (struct lambda) {church__pred____, __};
}

struct lambda church__pred__(struct lambda *_, struct lambda x)
{
	struct lambda *const __ = malloc(2 * sizeof(x));
	const struct lambda n = _[0];
	__[0] = _[1];
	__[1] = x;
	return lambda_call(lambda_call(lambda_call(n, (struct lambda) {
		church__pred___, __
	}), (struct lambda) {
		church__pred_____, __
	}), (struct lambda) {
		church__pred______, __
	});
}

struct lambda church__pred_(struct lambda *_, struct lambda f)
{
	struct lambda *const __ = malloc(2 * sizeof(f));
	__[0] = _[0];
	__[1] = f;
	return (struct lambda) {church__pred__, __};
}

struct lambda church__pred(struct lambda *, struct lambda n)
{
	struct lambda *const _ = malloc(sizeof(n));
	_[0] = n;
	return (struct lambda) {church__pred_, _};
}

const struct lambda church_pred = {church__pred};

struct lambda church_test__convert(struct lambda *, struct lambda x)
{
	return (struct lambda) {(lambda_t) ((uintptr_t) x.f + 1)};
}

unsigned int church_test_convert(struct lambda n)
{
	return (uintptr_t) lambda_call(lambda_call(n, (struct lambda) {
		church_test__convert
	}), (struct lambda) {
		(lambda_t) 0
	}).f;
}

void church_test_print(struct lambda n)
{
	printf("%u\n", church_test_convert(n));
}

int main()
{
	church_one = lambda_call(church_succ, church_zero);

	assert(logic_test_convert(logic_true) == true);
	assert(logic_test_convert(logic_false) == false);
	assert(logic_test_convert(lambda_call(lambda_call(logic_and, logic_true), logic_true)) == true);
	assert(logic_test_convert(lambda_call(lambda_call(logic_and, logic_true), logic_false)) == false);
	assert(logic_test_convert(lambda_call(lambda_call(logic_or, logic_true), logic_true)) == true);
	assert(logic_test_convert(lambda_call(lambda_call(logic_or, logic_true), logic_false)) == true);
	logic_test_print(logic_true);

	assert(church_test_convert(church_zero) == 0);
	assert(church_test_convert(lambda_call(church_succ, church_zero)) == 1);
	assert(church_test_convert(lambda_call(church_pred, lambda_call(church_succ, church_one))) == 1);
	church_test_print(church_one);
}
