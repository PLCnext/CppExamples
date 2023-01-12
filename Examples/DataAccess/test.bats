# This script is designed to be executed by bats (https://github.com/bats-core/)
# It requires bats-core to be installed, along with the submodules bats-support and bats-assert

setup() {
    load 'bats-support/load'
    load 'bats-assert/load'
    
    IP_ADDR="192.168.1.10"
    USERNAME="admin"
    PASSWORD="88f037bb"
}

@test "DataAccess Example" {
    # (Re)start the PLCnext Runtime
    run sshpass -p ${PASSWORD} ssh ${USERNAME}@${IP_ADDR} "echo ${PASSWORD} | sudo -S /etc/init.d/plcnext restart"
    assert_output --partial 'plcnext started'

    # Check the Output.log file for the expected messages
    run sshpass -p ${PASSWORD} ssh ${USERNAME}@${IP_ADDR} "timeout 60s tail -f -n 0 /opt/plcnext/logs/Output.log"
    assert_output --partial 'Array_OUT[0] from DataAccess Read() ='
    assert_output --partial 'Struct_OUT.MyInt16 from DataAccess Read() ='
    assert_output --partial 'Struct_OUT.MyString from DataAccess Read() ='
    assert_output --partial 'read from ReadSingle()'
}

#teardown() {
#}
