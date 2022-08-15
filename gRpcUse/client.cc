#include <string>
#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

// provide the interface for sending request to service: sendRequest().
class MathTestClient {
public:
    MathTestClient(std::shared_ptr<grpc::Channel> channel) 
    :stub_(mathTest::MathTest::NewStub(channel)) {}

    int sendRequest(int a, int b) {
        mathTest::MathRequest request;

        request.set_a(a);
        request.set_b(b);

        mathTest::MathReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->sendRequest(&context, request, &reply);

        if (status.ok()) {
            return reply.result();
        } else {
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return -1;
        }
    }
private:
    // stub_: used to sending request message to service and receive the result from service.
    std::unique_ptr<mathTest::MathTest::Stub> stub_;
};

// specify the service address and init the object client, call service interface by client to get the result.
void Run() {
    std::string address("0.0.0.0:50051");
    MathTestClient client(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        )
    );
    int response;
    int a = 5, b =10;
    response = client.sendRequest(a,b);
    std::cout << "Answer received:" << a << "*" << b << "=" << response << std::endl;
}

int main() {
    Run();
    return 0;
}