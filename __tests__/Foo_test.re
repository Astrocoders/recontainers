open Jest;

test("ok", () => {
  Expect.(
    expect(true) |> toBe(true)
  )
})
