#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct lambda;

typedef struct lambda (*lambda_t)(struct lambda *, struct lambda);

struct lambda {
	lambda_t fn;
	struct lambda *ctx;
};

struct lambda lambda_call(struct lambda lambda, struct lambda arg)
{
	return lambda.fn(lambda.ctx, arg);
}

struct lambda logic__true_(struct lambda *ctx, struct lambda _)
{
	const struct lambda x = ctx[0];
	return x;
}

struct lambda logic__true(struct lambda *_, struct lambda x)
{
	struct lambda result = {logic__true_};
	struct lambda *const ctx = malloc(sizeof(x));
	ctx[0] = x;
	result.ctx = ctx;
	return result;
}

const struct lambda logic_true = {logic__true};

struct lambda logic__false_(struct lambda *_, struct lambda y)
{
	return y;
}

struct lambda logic__false(struct lambda *_0, struct lambda _1)
{
	const struct lambda result = {logic__false_};
	return result;
}

const struct lambda logic_false = {logic__false};

struct lambda logic__not(struct lambda *_, struct lambda x)
{
	return lambda_call(lambda_call(x, logic_false), logic_true);
}

const struct lambda logic_not = {logic__not};

struct lambda logic__and_(struct lambda *ctx, struct lambda y)
{
	const struct lambda x = ctx[0];
	return lambda_call(lambda_call(x, y), logic_false);
}

struct lambda logic__and(struct lambda *_, struct lambda x)
{
	struct lambda result = {logic__and_};
	struct lambda *const ctx = malloc(sizeof(x));
	ctx[0] = x;
	result.ctx = ctx;
	return result;
}

const struct lambda logic_and = {logic__and};

struct lambda logic__or_(struct lambda *ctx, struct lambda y)
{
	const struct lambda x = ctx[0];
	return lambda_call(lambda_call(x, logic_true), y);
}

struct lambda logic__or(struct lambda *_, struct lambda x)
{
	struct lambda result = {logic__or_};
	struct lambda *const ctx = malloc(sizeof(x));
	ctx[0] = x;
	result.ctx = ctx;
	return result;
}

const struct lambda logic_or = {logic__or};

bool logic_test_convert(struct lambda x)
{
	const struct lambda arg0 = {(lambda_t) true};
	const struct lambda arg1 = {(lambda_t) false};
	return (uintptr_t) lambda_call(lambda_call(x, arg0), arg1).fn;
}

void logic_test_print(struct lambda x)
{
	printf("%hhu\n", logic_test_convert(x));
}

struct lambda church__zero_(struct lambda *_, struct lambda x)
{
	return x;
}

struct lambda church__zero(struct lambda *_0, struct lambda _1)
{
	const struct lambda result = {church__zero_};
	return result;
}

const struct lambda church_zero = {church__zero};

struct lambda church__succ__(struct lambda *ctx, struct lambda x)
{
	const struct lambda n = ctx[0];
	const struct lambda f = ctx[1];
	return lambda_call(f, lambda_call(lambda_call(n, f), x));
}

struct lambda church__succ_(struct lambda *ctx, struct lambda f)
{
	struct lambda result = {church__succ__};
	struct lambda *const ctx_ = malloc(2 * sizeof(f));
	ctx_[0] = ctx[0];
	ctx_[1] = f;
	result.ctx = ctx_;
	return result;
}

struct lambda church__succ(struct lambda *_, struct lambda n)
{
	struct lambda result = {church__succ_};
	struct lambda *const ctx = malloc(2 * sizeof(n));
	ctx[0] = n;
	result.ctx = ctx;
	return result;
}

const struct lambda church_succ = {church__succ};

struct lambda church_one;

struct lambda church__pred______(struct lambda *_, struct lambda a)
{
	return a;
}

struct lambda church__pred_____(struct lambda *ctx, struct lambda _)
{
	const struct lambda x = ctx[1];
	return x;
}

struct lambda church__pred____(struct lambda *ctx, struct lambda h)
{
	const struct lambda f = ctx[0];
	const struct lambda g = ctx[1];
	return lambda_call(h, lambda_call(g, f));
}

struct lambda church__pred___(struct lambda *ctx, struct lambda g)
{
	struct lambda result = {church__pred____};
	struct lambda *const ctx_ = malloc(2 * sizeof(g));
	ctx_[0] = ctx[0];
	ctx_[1] = g;
	result.ctx = ctx_;
	return result;
}

struct lambda church__pred__(struct lambda *ctx, struct lambda x)
{
	struct lambda arg0 = {church__pred___};
	struct lambda arg1 = {church__pred_____};
	struct lambda arg2 = {church__pred______};
	struct lambda *const ctx_ = malloc(2 * sizeof(x));
	const struct lambda n = ctx[0];
	ctx_[0] = ctx[1];
	ctx_[1] = x;
	arg0.ctx = ctx_;
	arg1.ctx = ctx_;
	arg2.ctx = ctx_;
	return lambda_call(lambda_call(lambda_call(n, arg0), arg1), arg2);
}

struct lambda church__pred_(struct lambda *ctx, struct lambda f)
{
	struct lambda result = {church__pred__};
	struct lambda *const ctx_ = malloc(2 * sizeof(f));
	ctx_[0] = ctx[0];
	ctx_[1] = f;
	result.ctx = ctx_;
	return result;
}

struct lambda church__pred(struct lambda *_, struct lambda n)
{
	struct lambda result = {church__pred_};
	struct lambda *const ctx = malloc(sizeof(n));
	ctx[0] = n;
	result.ctx = ctx;
	return result;
}

const struct lambda church_pred = {church__pred};

struct lambda church_test__convert(struct lambda *_, struct lambda x)
{
	struct lambda result;
	result.fn = (lambda_t) ((uintptr_t) x.fn + 1);
	return result;
}

unsigned int church_test_convert(struct lambda n)
{
	const struct lambda arg0 = {church_test__convert};
	const struct lambda arg1 = {(lambda_t) 0};
	return (uintptr_t) lambda_call(lambda_call(n, arg0), arg1).fn;
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

	return EXIT_SUCCESS;
}
