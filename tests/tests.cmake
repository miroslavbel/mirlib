function(mir_test_add test_name)
    add_test(NAME ${test_name} COMMAND libmirtestdriver "--test=${test_name}")
endfunction()
