#include <string>
#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

// implement the service
class MathServiceImpl final : public mathTest::MathTest::Service {
public:
    grpc::Status sendRequest(
        grpc::ServerContext* context,
        const mathTest::MathRequest* request,
        mathTest::MathReply* reply
    ) override {
        int a = request->a();
        int b = request->b();

        reply->set_result(a*b);

        return grpc::Status::OK;
    }
};

// service register
void Run() {

    std::string address("0.0.0.0:50051");
    MathServiceImpl service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port:" << address << std::endl;

    server->Wait();
}

// Start service
int main() {
    Run();
    return 0;
}