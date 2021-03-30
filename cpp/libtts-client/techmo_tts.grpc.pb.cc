// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: techmo_tts.proto

#include "techmo_tts.pb.h"
#include "techmo_tts.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace techmo {
namespace tts {
namespace grpc_api {

static const char* TTS_method_names[] = {
  "/techmo.tts.grpc_api.TTS/ListVoices",
  "/techmo.tts.grpc_api.TTS/SynthesizeStreaming",
  "/techmo.tts.grpc_api.TTS/Synthesize",
  "/techmo.tts.grpc_api.TTS/PutLexicon",
  "/techmo.tts.grpc_api.TTS/DeleteLexicon",
  "/techmo.tts.grpc_api.TTS/GetLexicon",
  "/techmo.tts.grpc_api.TTS/ListLexicons",
};

std::unique_ptr< TTS::Stub> TTS::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TTS::Stub> stub(new TTS::Stub(channel));
  return stub;
}

TTS::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_ListVoices_(TTS_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SynthesizeStreaming_(TTS_method_names[1], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_Synthesize_(TTS_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_PutLexicon_(TTS_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DeleteLexicon_(TTS_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetLexicon_(TTS_method_names[5], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListLexicons_(TTS_method_names[6], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status TTS::Stub::ListVoices(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest& request, ::techmo::tts::grpc_api::ListVoicesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ListVoices_, context, request, response);
}

void TTS::Stub::experimental_async::ListVoices(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest* request, ::techmo::tts::grpc_api::ListVoicesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ListVoices_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::ListVoices(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::ListVoicesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ListVoices_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::ListVoices(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest* request, ::techmo::tts::grpc_api::ListVoicesResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ListVoices_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::ListVoices(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::ListVoicesResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ListVoices_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::ListVoicesResponse>* TTS::Stub::AsyncListVoicesRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::ListVoicesResponse>::Create(channel_.get(), cq, rpcmethod_ListVoices_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::ListVoicesResponse>* TTS::Stub::PrepareAsyncListVoicesRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::ListVoicesResponse>::Create(channel_.get(), cq, rpcmethod_ListVoices_, context, request, false);
}

::grpc::ClientReader< ::techmo::tts::grpc_api::SynthesizeResponse>* TTS::Stub::SynthesizeStreamingRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request) {
  return ::grpc_impl::internal::ClientReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(channel_.get(), rpcmethod_SynthesizeStreaming_, context, request);
}

void TTS::Stub::experimental_async::SynthesizeStreaming(::grpc::ClientContext* context, ::techmo::tts::grpc_api::SynthesizeRequest* request, ::grpc::experimental::ClientReadReactor< ::techmo::tts::grpc_api::SynthesizeResponse>* reactor) {
  ::grpc_impl::internal::ClientCallbackReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_SynthesizeStreaming_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::techmo::tts::grpc_api::SynthesizeResponse>* TTS::Stub::AsyncSynthesizeStreamingRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc_impl::internal::ClientAsyncReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(channel_.get(), cq, rpcmethod_SynthesizeStreaming_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::techmo::tts::grpc_api::SynthesizeResponse>* TTS::Stub::PrepareAsyncSynthesizeStreamingRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(channel_.get(), cq, rpcmethod_SynthesizeStreaming_, context, request, false, nullptr);
}

::grpc::Status TTS::Stub::Synthesize(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request, ::techmo::tts::grpc_api::SynthesizeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Synthesize_, context, request, response);
}

void TTS::Stub::experimental_async::Synthesize(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest* request, ::techmo::tts::grpc_api::SynthesizeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Synthesize_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::Synthesize(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::SynthesizeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Synthesize_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::Synthesize(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest* request, ::techmo::tts::grpc_api::SynthesizeResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Synthesize_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::Synthesize(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::SynthesizeResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Synthesize_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::SynthesizeResponse>* TTS::Stub::AsyncSynthesizeRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(channel_.get(), cq, rpcmethod_Synthesize_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::SynthesizeResponse>* TTS::Stub::PrepareAsyncSynthesizeRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::SynthesizeResponse>::Create(channel_.get(), cq, rpcmethod_Synthesize_, context, request, false);
}

::grpc::Status TTS::Stub::PutLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest& request, ::techmo::tts::grpc_api::PutLexiconResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_PutLexicon_, context, request, response);
}

void TTS::Stub::experimental_async::PutLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest* request, ::techmo::tts::grpc_api::PutLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_PutLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::PutLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::PutLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_PutLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::PutLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest* request, ::techmo::tts::grpc_api::PutLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_PutLexicon_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::PutLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::PutLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_PutLexicon_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::PutLexiconResponse>* TTS::Stub::AsyncPutLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::PutLexiconResponse>::Create(channel_.get(), cq, rpcmethod_PutLexicon_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::PutLexiconResponse>* TTS::Stub::PrepareAsyncPutLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::PutLexiconResponse>::Create(channel_.get(), cq, rpcmethod_PutLexicon_, context, request, false);
}

::grpc::Status TTS::Stub::DeleteLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest& request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DeleteLexicon_, context, request, response);
}

void TTS::Stub::experimental_async::DeleteLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest* request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DeleteLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::DeleteLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DeleteLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::DeleteLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest* request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_DeleteLexicon_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::DeleteLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_DeleteLexicon_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::DeleteLexiconResponse>* TTS::Stub::AsyncDeleteLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::DeleteLexiconResponse>::Create(channel_.get(), cq, rpcmethod_DeleteLexicon_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::DeleteLexiconResponse>* TTS::Stub::PrepareAsyncDeleteLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::DeleteLexiconResponse>::Create(channel_.get(), cq, rpcmethod_DeleteLexicon_, context, request, false);
}

::grpc::Status TTS::Stub::GetLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest& request, ::techmo::tts::grpc_api::GetLexiconResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetLexicon_, context, request, response);
}

void TTS::Stub::experimental_async::GetLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest* request, ::techmo::tts::grpc_api::GetLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::GetLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::GetLexiconResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetLexicon_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::GetLexicon(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest* request, ::techmo::tts::grpc_api::GetLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetLexicon_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::GetLexicon(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::GetLexiconResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetLexicon_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::GetLexiconResponse>* TTS::Stub::AsyncGetLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::GetLexiconResponse>::Create(channel_.get(), cq, rpcmethod_GetLexicon_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::GetLexiconResponse>* TTS::Stub::PrepareAsyncGetLexiconRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::GetLexiconResponse>::Create(channel_.get(), cq, rpcmethod_GetLexicon_, context, request, false);
}

::grpc::Status TTS::Stub::ListLexicons(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest& request, ::techmo::tts::grpc_api::ListLexiconsResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ListLexicons_, context, request, response);
}

void TTS::Stub::experimental_async::ListLexicons(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest* request, ::techmo::tts::grpc_api::ListLexiconsResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ListLexicons_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::ListLexicons(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::ListLexiconsResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ListLexicons_, context, request, response, std::move(f));
}

void TTS::Stub::experimental_async::ListLexicons(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest* request, ::techmo::tts::grpc_api::ListLexiconsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ListLexicons_, context, request, response, reactor);
}

void TTS::Stub::experimental_async::ListLexicons(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::techmo::tts::grpc_api::ListLexiconsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ListLexicons_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::ListLexiconsResponse>* TTS::Stub::AsyncListLexiconsRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::ListLexiconsResponse>::Create(channel_.get(), cq, rpcmethod_ListLexicons_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::techmo::tts::grpc_api::ListLexiconsResponse>* TTS::Stub::PrepareAsyncListLexiconsRaw(::grpc::ClientContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::techmo::tts::grpc_api::ListLexiconsResponse>::Create(channel_.get(), cq, rpcmethod_ListLexicons_, context, request, false);
}

TTS::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::ListVoicesRequest, ::techmo::tts::grpc_api::ListVoicesResponse>(
          std::mem_fn(&TTS::Service::ListVoices), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[1],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< TTS::Service, ::techmo::tts::grpc_api::SynthesizeRequest, ::techmo::tts::grpc_api::SynthesizeResponse>(
          std::mem_fn(&TTS::Service::SynthesizeStreaming), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::SynthesizeRequest, ::techmo::tts::grpc_api::SynthesizeResponse>(
          std::mem_fn(&TTS::Service::Synthesize), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::PutLexiconRequest, ::techmo::tts::grpc_api::PutLexiconResponse>(
          std::mem_fn(&TTS::Service::PutLexicon), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::DeleteLexiconRequest, ::techmo::tts::grpc_api::DeleteLexiconResponse>(
          std::mem_fn(&TTS::Service::DeleteLexicon), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::GetLexiconRequest, ::techmo::tts::grpc_api::GetLexiconResponse>(
          std::mem_fn(&TTS::Service::GetLexicon), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TTS_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TTS::Service, ::techmo::tts::grpc_api::ListLexiconsRequest, ::techmo::tts::grpc_api::ListLexiconsResponse>(
          std::mem_fn(&TTS::Service::ListLexicons), this)));
}

TTS::Service::~Service() {
}

::grpc::Status TTS::Service::ListVoices(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::ListVoicesRequest* request, ::techmo::tts::grpc_api::ListVoicesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::SynthesizeStreaming(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest* request, ::grpc::ServerWriter< ::techmo::tts::grpc_api::SynthesizeResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::Synthesize(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::SynthesizeRequest* request, ::techmo::tts::grpc_api::SynthesizeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::PutLexicon(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::PutLexiconRequest* request, ::techmo::tts::grpc_api::PutLexiconResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::DeleteLexicon(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::DeleteLexiconRequest* request, ::techmo::tts::grpc_api::DeleteLexiconResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::GetLexicon(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::GetLexiconRequest* request, ::techmo::tts::grpc_api::GetLexiconResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TTS::Service::ListLexicons(::grpc::ServerContext* context, const ::techmo::tts::grpc_api::ListLexiconsRequest* request, ::techmo::tts::grpc_api::ListLexiconsResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace techmo
}  // namespace tts
}  // namespace grpc_api
