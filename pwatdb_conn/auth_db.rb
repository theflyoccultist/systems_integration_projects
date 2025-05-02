# frozen_string_literal: true

require 'dotenv/load'
require 'openssl/hmac'
require 'mac-address'

# HMAC Client
class Hmac
  def self.call
    key = secret_key
    mac_address = MacAddress.address
    halt 404, 'Mac Address not found' if mac_address.nil?

    timestamp = Time.now.to_i
    message = "#{mac_address}:#{timestamp}"
    mac = calc_digest(key, message)
    { signature: mac, timestamp: timestamp, mac_address: mac_address }
  end

  def self.secret_key
    ENV['API_DB_KEY'] || raise('Missing API_DB_KEY')
  end

  def self.calc_digest(key, message)
    OpenSSL::HMAC.hexdigest('sha256', key, message)
  end
end
