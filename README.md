# Cstack

Basic Stack implementation using ruby c extension.

## Installation

Add this line to your application's Gemfile:

    gem 'cstack'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cstack

## Usage

```
>> s = CStack::Stack.new
>> 1.upto(10){|i| s<< i}
>> while not s.empty? do p s.pop end
10
9
8
7
6
5
4
3
2
1
```

## Contributing

1. Fork it ( https://github.com/mgarcs/cstack/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request
