import torch

x = torch.ones(4, 6)
y = torch.zeros(4, 3)
w = torch.randn(6, 3, requires_grad=True)
b = torch.randn(4, 3, requires_grad=True)

# construct graph
"""
   x   w
    \ /
    MUL   b
      \  /
       ADD
        |
        z
z = add(mul(x,w), b)
"""
mul = torch.matmul(x, w)
add = mul + b
z = add
# define loss
loss = torch.nn.functional.binary_cross_entropy_with_logits(z, y)

print(dir(add.grad_fn))
print(dir(add.grad_fn.next_functions))
print(f"size of add.grad_fn.next_functions: {len(add.grad_fn.next_functions)}")
print(f"***** mul.grag_fn: *****\n{mul.grad_fn}")
print(f"***** add.grag_fn: *****\n{add.grad_fn}")
print(f"***** z.grag_fn: *****\n{z.grad_fn}")
print(f"***** loss.grag_fn: *****\n{loss.grad_fn}")
print(f"***** w.grag: *****\n{w.grad}")
print(f"***** b.grag: *****\n{b.grad}")

# AddBackward0 grad is all 1
print(loss.grad_fn.next_functions[0][0])
xxx = torch.rand(6, 3)
yyy = loss.grad_fn.next_functions[0][0](xxx)
torch.testing.assert_close(xxx, yyy[0])

print(z.grad_fn.next_functions[0][0])
xxx = torch.ones(4, 3)
yyy = z.grad_fn.next_functions[0][0](xxx)
print(yyy[0])
print(yyy[1])

# calculate grad
# w.grad: d(loss)/d(w)  -> [6,3]
# b.grad = d(loss)/d(b) -> [4,3]
loss.backward()
