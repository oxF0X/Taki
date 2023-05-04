#include "JsonRequestPacketSerializer.h"

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(ErrorResponse err)
{
    nlohmann::json j;
    err.to_json(j, err);
    return buildMsg(j, ERROR_RES);
}

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(LoginResponse l)
{
    nlohmann::json j;
    l.to_json(j, l);
    std::cout << j << std::endl;
    return buildMsg(j, LOGIN_RES);
}

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(SignupResponse s)
{
    nlohmann::json j;
    s.to_json(j, s);
    return buildMsg(j, Signup_RES);
}


std::vector<uint8_t> JsonRequestPacketSerializer::buildMsg(nlohmann::json j, unsigned int id)
{
    std::string str = j.dump();
    std::vector<std::uint8_t> data(str.begin(), str.end());
    std::vector<uint8_t> msg;
    std::vector<uint8_t> data_size = Helper::intToBytes(data.size());
    msg.push_back(id);
    std::copy(data_size.begin(), data_size.end(), std::back_inserter(msg));
    std::copy(data.begin(), data.end(), std::back_inserter(msg));
    return msg;
}
