$:.push File.expand_path( "../ruby", __FILE__ )
require "trema/version"

Gem::Specification.new do | s |
  s.name = "trema"
  s.version = Trema::VERSION
  s.authors = [ "Yasuhito Takamiya" ]
  s.email = [ "yasuhito@gmail.com" ]
  s.homepage = "http://github.com/trema/trema"
  s.summary = %q{Full-Stack OpenFlow Framework for Ruby and C}
  s.description = %q{Trema is a full-stack, easy-to-use framework for developing OpenFlow controllers in Ruby and C}
  s.license = "GPL2"

  ignores = File.readlines(".gitignore").grep(/\S+/).map {|s| s.chomp }
  s.files = Dir.glob("**/*", File::FNM_DOTMATCH).reject {|f| File.directory?(f) || f =~ /^\.git\// || f =~ /^\.gitignore$/ || ignores.any? {|i| File.fnmatch(i, f) } }
  s.test_files = s.files.grep(/^(spec|features)\//)

  s.bindir = "."
  s.executables = [ "trema", "trema-config" ]
  s.require_path = "ruby"
  s.extensions = [ "Rakefile" ]
  s.extra_rdoc_files = [ "README.md" ]

  # specify any dependencies here; for example:
  # s.add_development_dependency "rspec"
  s.add_runtime_dependency "rake"
  s.add_runtime_dependency "gli","2.0.0"

  s.add_development_dependency "rake"
  s.add_development_dependency "rdoc"
  s.add_development_dependency "aruba"
  s.add_development_dependency "rant"
end


### Local variables:
### mode: Ruby
### coding: utf-8-unix
### indent-tabs-mode: nil
### End:
