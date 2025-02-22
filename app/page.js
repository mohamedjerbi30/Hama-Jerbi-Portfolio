import Head from "next/head";
import FormationTimeline from "./Foramtion";

export default function Home() {
  return (
    <div className="bg-gray-900 text-white min-h-screen">
      <Head>
      <link
    rel="stylesheet"
    href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css"
  />
        <title>My Portfolio</title>
      </Head>
      <nav className="p-5 bg-gray-800 shadow-md">
        <div className="container mx-auto flex justify-between items-center">
          <h1 className="text-xl font-bold">Mohamed Jerbi</h1>
          <div>
            <a href="#experience" className="mx-2 hover:text-gray-400">Experience</a>
            <a href="#skills" className="mx-2 hover:text-gray-400">Skills</a>
            <a href="#projects" className="mx-2 hover:text-gray-400">Projects</a>
            <a href="#FormationTimeline" className="mx-2 hover:text-gray-400">Formation</a>
            <a href="#contact" className="mx-2 hover:text-gray-400">Contact</a>
          </div>
        </div>
      </nav>

      {/* Hero Section */}
      <header className="flex flex-col items-center justify-center text-center h-screen">
        <h2 className="text-4xl font-bold">Hello, I'm <span className="text-blue-400">Mohamed Jerbi</span></h2>
        <h3 className="text-xl mt-2 text-gray-400">First Year Telecommunication Ingineering Student and a full stack developper</h3>
        <p className="mt-4 text-gray-400">I am a passionate web developer and designer with extensive experience in <b> HTML, CSS, JavaScript, React.js, and Next.js.</b>
           My journey in the tech world has also led me to explore <b>WordPress, data science, and UX/UI design with Figma.</b> I thrive on building dynamic web applications,
            crafting interactive user interfaces, and diving into data-driven insights to create seamless, engaging experiences.</p>
        <a href="#contact" className="mt-4 px-5 py-2 bg-blue-500 text-white rounded-md hover:bg-blue-600">
          Get in Touch
        </a>
      </header>
      {/* Experience Section */}
      <section id="experience" className="py-20 px-6 bg-gray-800">
        <div className="container mx-auto text-center">
          <h3 className="text-3xl font-semibold text-blue-400">Experience</h3>
          <div className="mt-6">
            <p className="text-lg text-gray-300 font-semibold">Actif Member - Enit Junior Entreprise</p>
            <p className="text-gray-400">2024 - 2025</p>
            <p className="text-gray-400 mt-2">
            At <b>ENIT Junior Entreprise </b>, I had the opportunity to enhance my skills in <b>web development </b>, learning how to build responsive and interactive websites.
             I also contributed to organizing <b>the Forum ENIT Entreprise </b>,
             which involved coordinating with companies and helping set up an event for students and professionals to connect. Additionally, I led a workshop on <b>Figma</b>,
              focused on web and mobile design, where participants learned essential techniques for creating effective interfaces. 
            This experience allowed me to grow both technically and in event management, strengthening my teamwork and leadership abilities.
            </p>
          </div>
        </div>
      </section>

      {/* Skills Section */}
      <section id="skills" className="py-20 px-6">
        <div className="container mx-auto text-center">
          <h3 className="text-3xl font-semibold text-blue-400">Skills</h3>
          <div className="flex flex-wrap justify-center mt-6">
            {["React", "Next.js", "Wordpress", "Python", "Machine Learning", "Data Science", "Figma"].map((skill) => (
              <span key={skill} className="bg-gray-700 px-4 py-2 m-2 rounded-md">
                {skill}
              </span>
            ))}
          </div>
        </div>
      </section>

      {/* Projects Section */}
      <section id="projects" className="py-20 px-6 bg-gray-800">
  <div className="container mx-auto text-center">
    <h3 className="text-3xl font-semibold text-blue-400">Projects</h3>
    <div className="mt-6 grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
      {/* Project 1 */}
      <div className="bg-gray-700 p-6 rounded-lg shadow-lg">
        <img
          src="[Image URL]"
          alt="Project 1"
          className="w-full h-48 object-cover rounded-md mb-4"
        />
        <h4 className="text-xl text-white font-semibold">Project Name 1</h4>
        <p className="text-gray-300 mt-2">A short description of what this project does and the technologies used.</p>
      </div>
      {/* Project 2 */}
      <div className="bg-gray-700 p-6 rounded-lg shadow-lg">
        <img
          src="[Image URL]"
          alt="Project 2"
          className="w-full h-48 object-cover rounded-md mb-4"
        />
        <h4 className="text-xl text-white font-semibold">Project Name 2</h4>
        <p className="text-gray-300 mt-2">A short description of what this project does and the technologies used.</p>
      </div>
      {/* Project 3 */}
      <div className="bg-gray-700 p-6 rounded-lg shadow-lg">
        <img
          src="[Image URL]"
          alt="Project 3"
          className="w-full h-48 object-cover rounded-md mb-4"
        />
        <h4 className="text-xl text-white font-semibold">Project Name 3</h4>
        <p className="text-gray-300 mt-2">A short description of what this project does and the technologies used.</p>
      </div>
    </div>
  </div>
</section>

<FormationTimeline id="FormationTimeline"></FormationTimeline>


      {/* Contact Section */}
<section id="contact" className="py-20 px-6">
  <div className="container mx-auto text-center">
    <h3 className="text-3xl font-semibold text-blue-400">Contact Me</h3>
    <p className="mt-4 text-gray-400">Feel free to reach out for collaborations or any inquiries.</p>
    <form className="mt-6 max-w-md mx-auto">
      <div className="mb-4">
        <label htmlFor="name" className="block text-left text-lg font-semibold text-gray-300">Name</label>
        <input
          type="text"
          id="name"
          name="name"
          required
          className="w-full p-3 mt-2 bg-gray-700 text-gray-300 rounded-md"
          placeholder="Enter your name"
        />
      </div>
      <div className="mb-4">
        <label htmlFor="email" className="block text-left text-lg font-semibold text-gray-300">Email</label>
        <input
          type="email"
          id="email"
          name="email"
          required
          className="w-full p-3 mt-2 bg-gray-700 text-gray-300 rounded-md"
          placeholder="Enter your email"
        />
      </div>
      <div className="mb-4">
        <label htmlFor="comment" className="block text-left text-lg font-semibold text-gray-300">Comment</label>
        <textarea
          id="comment"
          name="comment"
          required
          className="w-full p-3 mt-2 bg-gray-700 text-gray-300 rounded-md"
          rows="4"
          placeholder="Enter your comment"
        ></textarea>
      </div>
      <button type="submit" className="mt-4 px-6 py-3 bg-blue-500 text-white rounded-md hover:bg-blue-600">
        Send Message
      </button>
    </form>
  </div>
</section>


      {/* Footer */}
      <footer className="p-6 bg-gray-800 text-center text-gray-400">
  <div className="flex justify-center space-x-8 mb-6">
    <a href="#home" className="text-gray-400 hover:text-blue-400">Home</a>
    <a href="#about" className="text-gray-400 hover:text-blue-400">About</a>
    <a href="#skills" className="text-gray-400 hover:text-blue-400">Skills</a>
    <a href="#projects" className="text-gray-400 hover:text-blue-400">Projects</a>
    <a href="#contact" className="text-gray-400 hover:text-blue-400">Contact</a>
  </div>

  <p className="text-gray-400 mt-4">
    © {new Date().getFullYear()} Mohamed Jerbi. All Rights Reserved.
  </p>
</footer>


</div>  
  );
}
