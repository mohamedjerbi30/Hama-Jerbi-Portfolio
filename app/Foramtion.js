// components/FormationTimeline.js
import React from 'react';

const FormationTimeline = () => {
  return (
    <div className="timeline" id="FormationTimeline">
      <h3 className="text-2xl font-semibold text-center mb-6">My Formation Timeline</h3>
      <section className= "container mx-auto">
      <ul className="space-y-4">
        <li className="flex items-center space-x-4">
          <div className="w-10 h-10 bg-blue-500 text-white rounded-full flex items-center justify-center">1</div>
          <div className="flex-1">
            <h4 className="font-semibold">Cursus 1</h4>
            <h5 className="text-gray-400">2018-2020</h5>
            <p className="text-gray-400">High School Student in Carthage Byrsa</p>
          </div>
        </li>
        <li className="flex items-center space-x-4">
          <div className="w-10 h-10 bg-blue-500 text-white rounded-full flex items-center justify-center">2</div>
          <div className="flex-1">
            <h4 className="font-semibold">Cursus 2</h4>
            <h5 className="text-gray-400">2020-2022</h5>
            <p className="text-gray-400">High School Student in Carthage Presidence</p>
          </div>
        </li>
        <li className="flex items-center space-x-4">
          <div className="w-10 h-10 bg-blue-500 text-white rounded-full flex items-center justify-center">3</div>
          <div className="flex-1">
            <h4 className="font-semibold">Cursus 3</h4>
            <h5 className="text-gray-400">2022-2024</h5>
            <p className="text-gray-400">Preparatory Ingineering Student</p>
          </div>
        </li>
        <li className="flex items-center space-x-4">
          <div className="w-10 h-10 bg-blue-500 text-white rounded-full flex items-center justify-center">4</div>
          <div className="flex-1">
            <h4 className="font-semibold">Cursus 4</h4>
            <h5 className="text-gray-400">2024-2027</h5>
            <p className="text-gray-400">Telecommunication Ingineering Student</p>
          </div>
        </li>
      </ul>
      </section>
    </div>
  );
};

export default FormationTimeline;
